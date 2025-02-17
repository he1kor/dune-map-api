#include "block_placer.h"
#include "global.h"
#include <vector>
#include <utility>
#include <stdexcept>
#include <util.h>

BlockPlacer::BlockPlacer() : placement_history{HistoryStack<BlockStamp>(*this)}{}

BlockPlacer::BlockPlacer(BlockSet *block_set) : block_set{block_set}, compatible_checker{block_set->getCompatibleChecker()}, placement_history{HistoryStack<BlockStamp>(*this)}{}

void BlockPlacer::setMap(SmartMap *map){
    this->map = map;
}

void BlockPlacer::setBlockSet(BlockSet *block_set){
    this->block_set = block_set;
    this->compatible_checker = block_set->getCompatibleChecker();
}
        //TODO: add out of map support
void BlockPlacer::place(int x, int y, const Block &block){
    std::vector<std::vector<uint16_t>> tiles = block.getMatrix();
    for (int r = 0; r < block.getHeight(); r++){
        for (int c = 0; c < block.getWidth(); c++){
            map->addTileID(x+c, y+r, tiles[r][c]);
        }
    }
    placement_history.quickCommit(BlockStamp{x, y, block.getWidth(), block.getHeight()});
    map->commit();
}
std::vector<CompatibleType> BlockPlacer::getCompatibleTypesFacingEdge(const Edge &edge, const d2kmapapi::Direction &direction){
    DirectionalLine line = map->getLineFacingEdge(edge, direction);
    return compatible_checker->compatibleTypes(line);
}

int BlockPlacer::getQuickShift(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block){
    return block_set->getQuickShift(map->getLineFacingEdge(edge, direction), block);
}

std::pair<int, int> BlockPlacer::smartEdgePlace(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block){
    return placeOnEdgeShifted(edge, direction, block, getQuickShift(edge, direction, block));
}
std::pair<int, int> BlockPlacer::getSmartEdgePlaceCoords(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block){
    return getPlaceOnEdgeShiftedCoords(edge, direction, block, getQuickShift(edge, direction, block));
}
std::pair<int, int> BlockPlacer::getPlaceOnEdgeShiftedCoords(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block, int shift){
    checkPerpendicularToEdge(edge, direction);
    auto [x, y] = edge.onAfter()[0];
    
    switch (direction){
        case d2kmapapi::Direction::DOWN:
            x -= shift;
            break;
        case d2kmapapi::Direction::LEFT:
            x -= block.getWidth();
            y -= shift;
            break;
        case d2kmapapi::Direction::UP:
            x -= shift;
            y -= block.getHeight();
            break;
        case d2kmapapi::Direction::RIGHT:
            y -= shift;
            break;
        }
    return {x, y};
}
std::pair<int, int> BlockPlacer::placeOnEdgeShifted(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block, int shift){
    auto [x, y] = getPlaceOnEdgeShiftedCoords(edge, direction, block, shift);
    place(x, y, block);
    return {x, y};
}
std::pair<int, int> BlockPlacer::placeOnEdge(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block){
    if (block.getSizeAlongDirection(direction) != edge.getSize())
        throw std::invalid_argument("Sizes don't fit!");
    return placeOnEdgeShifted(edge, direction, block, 0);
}
DirectedEdge BlockPlacer::getSideEdge(const Block &block, const d2kmapapi::Direction &direction, int x, int y, int offset, int size){
    size--;
    switch (direction){
        case d2kmapapi::Direction::UP:
            return DirectedEdge(Horizontal::fromBottom(x+offset, x+offset+size, y), direction);
        case d2kmapapi::Direction::LEFT:
            return DirectedEdge(Vertical::fromRight(y+offset, y+offset+size, x), direction);
        case d2kmapapi::Direction::RIGHT:
            return DirectedEdge(Vertical::fromRight(y+offset, y+offset+size, x+block.getWidth()), direction);
        case d2kmapapi::Direction::DOWN:
            return DirectedEdge(Horizontal::fromBottom(x+offset, x+offset+size, y+block.getHeight()), direction);
        default:
            throw std::invalid_argument("Unknown direction " + direction);
    }
}
DirectedEdge BlockPlacer::smartPlaceNextOnEdge(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block, std::set<CompatibleType> nextEdgeTypes){
    auto [x, y] = smartEdgePlace(edge, direction, block);
    return findNextEdgeOnBlock(block, x, y, d2kmapapi::reverse(direction), nextEdgeTypes);
}
DirectedEdge BlockPlacer::placeNextOnEdge(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block, std::set<CompatibleType> nextEdgeTypes){
    auto [x, y] = placeOnEdge(edge, direction, block);
    return findNextEdgeOnBlock(block, x, y, d2kmapapi::reverse(direction), nextEdgeTypes);
}
//todo: cache next edge offset of block
DirectedEdge BlockPlacer::findNextEdgeOnBlock(const Block &block, int x, int y, const d2kmapapi::Direction &excluded_direction, const std::set<CompatibleType> &edge_types){
    std::set<d2kmapapi::Direction> directions = {d2kmapapi::Direction::DOWN, d2kmapapi::Direction::LEFT, d2kmapapi::Direction::RIGHT, d2kmapapi::Direction::UP};
    directions.erase(excluded_direction);
    for (auto direction : directions){ 
        auto line = compatible_checker->compatibleTypes(block.getDirectionalOutLine(direction));
        int size = 0;
        for (int i = 0; i < line.size(); i++){
            while (i < line.size() && edge_types.count(line[i])){
                size++;
                i++;
            }
            if (size){
                return getSideEdge(block, direction, x, y, i-size, size);
            }
        }
    }
    throw std::runtime_error("No next edge on block found");
}
bool BlockPlacer::isEdgeCompatible(const Edge &edge) const{
    d2kmapapi::Direction direction;
    if (edge.getOrientation() == Orientation::horizontal)
        direction = d2kmapapi::Direction::RIGHT;
    else
        direction = d2kmapapi::Direction::DOWN;
    
    std::vector<std::pair<int, int>> coords1 = edge.onBefore();
    std::vector<std::pair<int, int>> coords2 = edge.onAfter();
    for (int i = 0; i < edge.getSize(); i++){
        auto [x1, y1] = coords1[i];
        auto [x2, y2] = coords2[i];
        if (!compatible_checker->areCompatible(
            map->getTileID(x1, y1),
            direction,
            map->getTileID(x2, y2)))
            return false;
    }
    return true;
}

std::vector<Block> BlockPlacer::compatibleBlocks(const Edge &edge, const d2kmapapi::Direction &direction, std::string group, std::set<CompatibleType> must_fit_types){
    std::vector<Block> possible_blocks = block_set->compatibleBlocks(map->getLineFacingEdge(edge, direction), group);
    std::vector<Block> result;
    for (auto block : possible_blocks){
        bool not_compatible = false;
        for (auto direction : d2kmapapi::directions){
            auto compatible_types_side = compatible_checker->compatibleTypes(block.getDirectionalOutLine(direction));
            for (int i = 0; i < block.getWidth(); i++){
                if (must_fit_types.count(compatible_types_side[i])){
                    auto [x, y] = getSmartEdgePlaceCoords(edge, direction, block);
                    if (!isEdgeCompatible(getSideEdge(block, direction, x, y, i, 1).getEdge())){
                        not_compatible = true;
                        goto skip_block;
                    }
                }
            }
        }
        skip_block:
        if (not_compatible)
            break;
        result.push_back(block);
    }
    return result;
}

std::vector<Block> BlockPlacer::compatibleBlocks(const Edge &edge, const d2kmapapi::Direction &direction, std::string group){
    return block_set->compatibleBlocks(map->getLineFacingEdge(edge, direction), group);
}

BlockStamp BlockPlacer::getOldState(const BlockStamp &changing_state) const{
    return last_block_stamp;
}

void BlockPlacer::applyChange(BlockStamp change){
    last_block_stamp = change;
}

void BlockPlacer::undoChange(BlockStamp old_state){
    last_block_stamp = old_state;
}

bool BlockPlacer::checkPerpendicularToEdge(const Edge &edge, const d2kmapapi::Direction &direction){
    if (!edge.isAlong(direction))
        return true;
    throw std::invalid_argument("Direction is not perpendicular to the edge!");
    return false;
}

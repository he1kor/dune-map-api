#include "block_placer.h"
#include "global.h"
#include <vector>
#include <utility>
#include <stdexcept>
#include <util.h>

BlockPlacer::BlockPlacer(){}

BlockPlacer::BlockPlacer(BlockSet *block_set) : block_set{block_set}, compatible_checker{block_set->getCompatibleChecker()}{}

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
std::pair<int, int> BlockPlacer::placeOnEdgeShifted(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block, int shift){
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
    place(x, y, block);
    return {x, y};
}
std::pair<int, int> BlockPlacer::placeOnEdge(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block){
    if (block.getSizeAlongDirection(direction) != edge.getSize())
        throw std::invalid_argument("Sizes don't fit!");
    return placeOnEdgeShifted(edge, direction, block, 0);
}
Edge BlockPlacer::getSideEdge(const Block &block, const d2kmapapi::Direction &direction, int x, int y, int offset, int size){
    size--;
    switch (direction){
        case d2kmapapi::Direction::UP:
            return Horizontal::fromBottom(x+offset, x+offset+size, y);
        case d2kmapapi::Direction::LEFT:
            return Vertical::fromRight(y+offset, y+offset+size, x);
        case d2kmapapi::Direction::RIGHT:
            return Vertical::fromRight(y+offset, y+offset+size, x+block.getWidth());
        case d2kmapapi::Direction::DOWN:
            return Horizontal::fromBottom(x+offset, x+offset+size, y+block.getHeight());
        default:
            throw std::invalid_argument("Unknown direction " + direction);
    }
}
Edge BlockPlacer::smartPlaceNextOnEdge(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block, std::set<CompatibleType> nextEdgeTypes){
    auto [x, y] = smartEdgePlace(edge, direction, block);
    return findNextEdgeOnBlock(block, x, y, d2kmapapi::reverse(direction), nextEdgeTypes);
}
Edge BlockPlacer::placeNextOnEdge(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block, std::set<CompatibleType> nextEdgeTypes){
    auto [x, y] = placeOnEdge(edge, direction, block);
    return findNextEdgeOnBlock(block, x, y, d2kmapapi::reverse(direction), nextEdgeTypes);
}
//todo: cache next edge offset of block
Edge BlockPlacer::findNextEdgeOnBlock(const Block &block, int x, int y, const d2kmapapi::Direction &excluded_direction, const std::set<CompatibleType> &edge_types){
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
            if (size)
                return getSideEdge(block, direction, x, y, i, size);
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

std::vector<Block> BlockPlacer::compatibleBlocks(const Edge &edge, const d2kmapapi::Direction &direction, std::string group){
    return block_set->compatibleBlocks(map->getLineFacingEdge(edge, direction), group);
}

bool BlockPlacer::checkPerpendicularToEdge(const Edge &edge, const d2kmapapi::Direction &direction){
    if (!edge.isAlong(direction))
        return true;
    throw std::invalid_argument("Direction is not perpendicular to the edge!");
    return false;
}

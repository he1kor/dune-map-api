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
//done
void BlockPlacer::place(int x, int y, const Block &block){
    std::vector<std::vector<uint16_t>> tiles = block.getMatrix();
    for (int r = 0; r < block.getHeight(); r++){
        for (int c = 0; c < block.getWidth(); c++){
            map->addTileID(x+c, y+r, tiles[r][c]);
        }
    }
    map->commit();
}
//done
std::vector<CompatibleType> BlockPlacer::getCompatibleTypesFacingEdge(const Edge &edge, const d2kmapapi::Direction &direction){
    DirectionalLine line = map->getLineFacingEdge(edge, direction);
    return compatible_checker->compatibleTypes(line);
}

//done
int BlockPlacer::getQuickShift(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block){
    return block_set->getQuickShift(map->getLineFacingEdge(edge, direction), block);
}

//TODO:: DO
int BlockPlacer::nextBlockScore(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block, std::vector<CompatibleType> block_next_compatible, std::vector<CompatibleType> temp_next){
    int shift = getQuickShift(edge, direction, block);
    std::vector<CompatibleType> block_bottom = compatible_checker->compatibleTypes(DirectionalLine(block.getBottomTiles(), d2kmapapi::Direction::DOWN));
    std::vector<CompatibleType> block_left = compatible_checker->compatibleTypes(DirectionalLine(block.getLeftTiles(), d2kmapapi::Direction::LEFT));
    std::vector<CompatibleType> block_right = compatible_checker->compatibleTypes(DirectionalLine(block.getRightTiles(), d2kmapapi::Direction::RIGHT));
    std::vector<CompatibleType> block_top = compatible_checker->compatibleTypes(DirectionalLine(block.getTopTiles(), d2kmapapi::Direction::UP));
    int x;
    int y;
    switch (direction){
        case d2kmapapi::Direction::DOWN:
            x = edge.onBefore()[0].first-shift-1;
            y = edge.onBefore()[0].second;
            break;
        case d2kmapapi::Direction::LEFT:
            x = edge.onBefore()[0].first-block.getWidth();
            y = edge.onBefore()[0].second-shift-1;
            break;
        case d2kmapapi::Direction::RIGHT:
            x = edge.onBefore()[0].first;
            y = edge.onBefore()[0].second-shift-1;
            break;
        case d2kmapapi::Direction::UP:
            x = edge.onBefore()[0].first-shift-1;
            y = edge.onBefore()[0].second-block.getHeight();
            break;
    }

    std::vector<uint16_t> out_tiles_bottom;
    std::vector<uint16_t> out_tiles_left;
    std::vector<uint16_t> out_tiles_right;
    std::vector<uint16_t> out_tiles_top;
    std::vector<CompatibleType> out_bottom;
    std::vector<CompatibleType> out_left;
    std::vector<CompatibleType> out_right;
    std::vector<CompatibleType> out_top;
    for (int x_i = x+1; x_i <= x+block.getWidth(); x_i++){
        out_tiles_top.push_back(map->getTileID(x_i, y));
        out_tiles_bottom.push_back(map->getTileID(x, y + block.getHeight()));
    }
    return 0;
}

void BlockPlacer::loopPlace(const Edge &edge, const d2kmapapi::Direction &direction, std::vector<std::vector<CompatibleType>> next_edges){
    HistoryStack loop_stack(map);
}

//Done
bool BlockPlacer::smartEdgePlace(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block){
    placeOnEdgeShifted(edge, direction, block, getQuickShift(edge, direction, block));
}
//done
bool BlockPlacer::placeOnEdgeShifted(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block, int shift){
    if (!checkPerpendicularToEdge(edge, direction))
        return false;
    auto [x, y] = edge.onAfter()[0];
    switch (direction){
        case d2kmapapi::Direction::DOWN:
            place(x-shift, y, block);
            break;
        case d2kmapapi::Direction::LEFT:
            place(x-block.getWidth(), y-shift, block);
            break;
        case d2kmapapi::Direction::UP:
            place(x-shift, y-block.getHeight(), block);
            break;
        case d2kmapapi::Direction::RIGHT:
            place(x, y-shift, block);
            break;
    }
    return true;
}
bool BlockPlacer::placeOnEdge(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block){
    if (block.getSizeAlongDirection(direction) != edge.getSize()){
        throw std::invalid_argument("Sizes don't fit!");
        return false;
    }
    return placeOnEdgeShifted(edge, direction, block, 0);
}
//done
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

bool BlockPlacer::checkPerpendicularToEdge(const Edge &edge, const d2kmapapi::Direction &direction){
    if (edge.isAlong(direction))
        return true;
    throw std::invalid_argument("Direction is not perpendicular to the edge!");
    return false;
}

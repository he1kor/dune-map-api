#include "block_placer.h"
#include "global.h"
#include <vector>
#include <utility>
#include <iostream>
#include <util.h>

BlockPlacer::BlockPlacer(){}

BlockPlacer::BlockPlacer(BlockSet *block_set) : block_set{block_set}, compatible_checker{block_set->getCompatibleChecker()}{}

void BlockPlacer::setHistoryStack(HistoryStack *history_stack){
    this->history_stack = history_stack;
}

void BlockPlacer::setMap(Map *map){
    this->map = map;
}

void BlockPlacer::setBlockSet(BlockSet *block_set){
    this->block_set = block_set;
    this->compatible_checker = block_set->getCompatibleChecker();
}

void BlockPlacer::place(int x, int y, const Block &block){
    std::vector<std::vector<uint16_t>> tiles = block.getMatrix();
    if (!history_stack){
        for (int r = 0; r < block.getHeight(); r++){
            for (int c = 0; c < block.getWidth(); c++){
                (*map)[y+r][x+c].tileID = tiles[r][c];
            }
        }
        return;
    }
    for (int r = 0; r < block.getHeight(); r++){
        for (int c = 0; c < block.getWidth(); c++){
            map[y+r][x+c] = tiles[r][c];
            history_stack->trackChange({
                {tiles[r][c], (*map)[r][c].entityID},
                x+c, y+r
            });
        }
    }
    history_stack->commit();
}

DirectionalLine BlockPlacer::edgeLine(const Edge &edge, const d2kmapapi::Direction &direction)
{
    std::vector<uint16_t> edge_tiles;
    for (auto [x, y] : direction == d2kmapapi::Direction::RIGHT || direction == d2kmapapi::Direction::DOWN ? edge.onAfter() : edge.onBefore()){
        edge_tiles.push_back((*map)[y][x].tileID);
    }
    return DirectionalLine(edge_tiles, d2kmapapi::reverse(direction));
}

std::vector<CompatibleType> BlockPlacer::edgeCompatible(const Edge &edge, const d2kmapapi::Direction &direction){
    DirectionalLine line = edgeLine(edge, direction);
    line.reverse();
    return compatible_checker->compatibleTypes(line);
}

int BlockPlacer::getShift(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block)
{
    std::vector<uint16_t> block_tiles;
    std::vector<std::pair<int, int>> edge_coords;
    switch (direction){
        case d2kmapapi::Direction::DOWN:
            block_tiles = block.getTopTiles();
            edge_coords = edge.onBefore();
            break;
        case d2kmapapi::Direction::LEFT:
            block_tiles = block.getRightTiles();
            edge_coords = edge.onAfter();
            break;
        case d2kmapapi::Direction::RIGHT:
            block_tiles = block.getLeftTiles();
            edge_coords = edge.onBefore();
            break;
        case d2kmapapi::Direction::UP:
            block_tiles = block.getBottomTiles();
            edge_coords = edge.onAfter();
            break;
    }
    std::vector<uint16_t> edge_tiles;
    for (auto [x, y] : edge_coords){
        edge_tiles.push_back((*map)[y][x].tileID);
    }
    auto block_compatibles = compatible_checker->compatibleTypes(DirectionalLine(block_tiles, d2kmapapi::reverse(direction)));
    auto edge_compatibles = compatible_checker->compatibleTypes(DirectionalLine(edge_tiles, direction));

    for (int i = 0; i <= block_compatibles.size() - edge_compatibles.size(); i++){
        for (int j = 0; j < edge_compatibles.size(); j++){
            if (block_compatibles[i+j] != edge_compatibles[j]){
                break;
            }
            if (j == edge_compatibles.size()-1)
                return i;
        }
    }
    return -1;
}

int BlockPlacer::nextBlockScore(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block, std::vector<CompatibleType> block_next_compatible, std::vector<CompatibleType> temp_next){
    int shift = getShift(edge, direction, block);
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
        out_tiles_top.push_back((*map)[x_i][y].tileID);
        out_tiles_bottom.push_back((*map)[x_i][y+block.getHeight()].tileID);
    }
    return 0;
}

void BlockPlacer::loopPlace(const Edge &edge, const d2kmapapi::Direction &direction, std::vector<std::vector<CompatibleType>> next_edges){
    HistoryStack loop_stack(map);
}

bool BlockPlacer::smartEdgePlace(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block){
    int block_length = block.getHeight();
    std::vector<uint16_t> block_tiles;
    std::vector<std::pair<int, int>> edge_line;
    switch (direction){
        case d2kmapapi::Direction::DOWN:
            block_tiles = block.getTopTiles();
            edge_line = edge.onBefore();
            break;
        case d2kmapapi::Direction::LEFT:
            block_tiles = block.getRightTiles();
            edge_line = edge.onAfter();
            break;
        case d2kmapapi::Direction::RIGHT:
            block_tiles = block.getLeftTiles();
            edge_line = edge.onBefore();
            break;
        case d2kmapapi::Direction::UP:
            block_tiles = block.getBottomTiles();
            edge_line = edge.onAfter();
            break;
    }

    
}

bool BlockPlacer::placeEdge(const Edge &edge, const d2kmapapi::Direction &direction, const Block &block)
{
    int block_length = block.getHeight();
    if (edge.getOrientation() == Orientation::horizontal)
        block_length = block.getWidth();
    if (block_length != edge.getSize()){
        throw std::runtime_error("Sizes don't fit!");
        return false;
    }
    auto [x, y] = edge.onAfter()[0];
    switch (direction){
        case d2kmapapi::Direction::DOWN:
            place(x, y, block);
            break;
        case d2kmapapi::Direction::LEFT:
            place(x-block.getWidth(), y, block);
            break;
        case d2kmapapi::Direction::UP:
            place(x, y-block.getHeight(), block);
            break;
        case d2kmapapi::Direction::RIGHT:
            place(x, y, block);
            break;
    }
    return true;
}

bool BlockPlacer::fit(const Edge &edge) const{
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
            (*map)[y1][x1].tileID,
            direction,
            (*map)[y2][x2].tileID))
            return false;
    }
    return true;
}
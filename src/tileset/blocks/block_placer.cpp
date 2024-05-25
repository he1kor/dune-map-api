#include "block_placer.h"
#include "global.h"
#include <vector>
#include <utility>
#include <iostream>
#include <util.h>

BlockPlacer::BlockPlacer(){}

BlockPlacer::BlockPlacer(BlockSet *block_set) : block_set{block_set}{}

void BlockPlacer::setHistoryStack(HistoryStack *history_stack){
    this->history_stack = history_stack;
}

void BlockPlacer::place(int x, int y, const Block &block){
    std::vector<std::vector<uint16_t>> tiles = block.getMatrix();
    if (!history_stack){
        for (int r = 0; r < tiles.size(); r++){
            for (int c = 0; c < tiles.size(); c++){
                map[y+r][x+c] = tiles[r][c];
            }
        }
        return;
    }
    for (int r = 0; r < tiles.size(); r++){
        for (int c = 0; c < tiles.size(); c++){
            map[y+r][x+c] = tiles[r][c];
            history_stack->trackChange({
                {tiles[r][c], (*map)[r][c].entityID},
                x+c, y+r
            });
        }
    }
    history_stack->commit();
}

bool BlockPlacer::placeEdge(const Edge &edge, const d2kmapapi::Direction& direction, const Block &block){
    int block_length = block.getHeight();
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

bool BlockPlacer::fit(const Edge &edge) const
{
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
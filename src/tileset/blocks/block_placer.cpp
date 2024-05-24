#include "block_placer.h"
#include "global.h"
#include <vector>
#include <utility>
#include <iostream>

BlockPlacer::BlockPlacer(){}

BlockPlacer::BlockPlacer(BlockSet *block_set) : block_set{block_set}{}

void BlockPlacer::place(int x, int y, const Block &block){
    std::vector<std::vector<uint16_t>> tiles = block.getMatrix();
    for (int r = 0; r < tiles.size(); r++){
        for (int c = 0; c < tiles.size(); c++){
            map[y+r][x+c] = tiles[r][c];
        }
    }
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
            (*map)[y1][y2].tileID,
            direction,
            (*map)[y1][y2].tileID))
            return false;
    }
    return true;
}
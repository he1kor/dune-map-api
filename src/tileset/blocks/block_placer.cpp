#include "block_placer.h"
#include "global.h"
#include <vector>
#include <utility>
#include <iostream>

Block::Block(int x, int y, int width, int height) : width{width}, height{height}{
    tiles = std::vector<std::vector<uint16_t>>(height, std::vector<uint16_t>());
    for (int r = 0; r < height; r++){
        left.push_back((r+y) * d2kmapapi::tileset_width + x);
        right.push_back((r+y) * d2kmapapi::tileset_width + x + width-1);
        for (int c = 0; c < width; c++){
            tiles[r].push_back((r+y) * d2kmapapi::tileset_width + (c+x));
        }
    }
}

Block::Block(const Block &block) : width(block.width), height(block.height){
    left = block.left;
    right = block.right;
    tiles = block.tiles;
}


std::vector<std::vector<uint16_t>> Block::getMatrix() const{
    return tiles;
}

std::vector<uint16_t> Block::getTopTiles() const{
    return tiles[0];
}
std::vector<uint16_t> Block::getLeftTiles() const{
    return left;
}
std::vector<uint16_t> Block::getRightTiles() const{
    return right;
}
std::vector<uint16_t> Block::getBottomTiles() const{
    return tiles[height-1];
}

int Block::getWidth() const{
    return width;
}
int Block::getHeight() const{
    return height;
}

void BlockPlacer::place(int x, int y, const Block& block){
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
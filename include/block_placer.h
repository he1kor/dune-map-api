#pragma once
#include <vector>
#include <cstdint>
#include "map.h"
#include "edge.h"
#include "compatible_checker.h"
class Block{
    public:
        Block(int x, int y, int width, int height);
        std::vector<std::vector<uint16_t>> getMatrix() const;
        std::vector<uint16_t> getTopTiles() const;
        std::vector<uint16_t> getLeftTiles() const;
        std::vector<uint16_t> getRightTiles() const;
        std::vector<uint16_t> getBottomTiles() const;
        const int width;
        const int height;
    private:
        std::vector<uint16_t> left;
        std::vector<uint16_t> right;
        std::vector<std::vector<uint16_t>> tiles;
};
class BlockPlacer{
    public:
        void place(int x, int y, const Block& block);
        bool fit(const Edge& edge) const;
    private:
        CompatibleChecker* compatible_checker;
        std::vector<Block> blocks;
        Map* map;
};
#pragma once
#include <vector>
#include <cstdint>
#include "compatible_checker.h"
class Block{
    public:
        Block(int x, int y, int width, int height);
        Block(const Block& block);
        std::vector<std::vector<uint16_t>> getMatrix() const;
        std::vector<uint16_t> getTopTiles() const;
        std::vector<uint16_t> getLeftTiles() const;
        std::vector<uint16_t> getRightTiles() const;
        std::vector<uint16_t> getBottomTiles() const;
        int getWidth() const;
        int getHeight() const;
    private:
        std::vector<uint16_t> left;
        std::vector<uint16_t> right;
        int width;
        int height;
        std::vector<std::vector<uint16_t>> tiles;
};
class BlockSet{
    public:
        BlockSet(const std::vector<Block>& blocks);
        BlockSet();
        void addCompatibleCheker(const CompatibleChecker* compatible_checker);
        void addBlock(const Block& block);
        std::vector<Block> compatibleBlocks(d2kmapapi::Direction direction);
    private:
        CompatibleChecker* compatible_checker;
        std::vector<Block> blocks;
};
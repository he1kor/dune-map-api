#pragma once
#include <vector>
#include <cstdint>
#include "directional_line.h"
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
        BlockSet(const std::map<std::string, std::vector<Block>>& blocks);
        BlockSet();
        void addCompatibleCheker(const CompatibleChecker* compatible_checker);
        void addGroup(const std::string& group);
        void addBlock(const Block& block, const std::string& group);
        std::vector<Block> operator[](std::string group) const;
        std::vector<Block> compatibleBlocks(const DirectionalLine& line, std::string group);
    private:
        const CompatibleChecker* compatible_checker;
        std::map<std::string, std::vector<Block>> block_groups;
};
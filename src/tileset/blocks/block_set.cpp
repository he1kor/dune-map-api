#include "block_set.h"
#include "global.h"
#include <stdexcept>
#include <format>
#include "util.h"

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

BlockSet::BlockSet(const std::map<std::string, std::vector<Block>> &block_groups, CompatibleChecker *compatible_checker) : block_groups{block_groups}, compatible_checker{compatible_checker}{}

BlockSet::BlockSet(const std::map<std::string, std::vector<Block>> &block_groups) : block_groups{block_groups} {}

BlockSet::BlockSet(){}

void BlockSet::addCompatibleCheker(CompatibleChecker *compatible_checker){
    this->compatible_checker = compatible_checker;
}

void BlockSet::addGroup(const std::string &group){
    if (block_groups.count(group))
        throw std::invalid_argument(std::format("Group \"{}\" already exists!", group));
    block_groups[group] = {};
}

void BlockSet::addBlock(const Block &block, const std::string& group){
    block_groups.at(group).push_back(block); 
}

std::vector<Block> BlockSet::operator[](std::string group) const{
    return block_groups.at(group);
}

std::vector<std::string> BlockSet::getGroups(){
    std::vector<std::string> groups;
    for (auto p : block_groups){
        groups.push_back(p.first);
    }
    return groups;
}

CompatibleChecker *BlockSet::getCompatibleChecker() const{
    return compatible_checker;
}

std::vector<Block> BlockSet::compatibleBlocks(const DirectionalLine& line, std::string group_name){
    std::vector<Block> compatible_blocks;
    std::vector<CompatibleType> compatible_types = compatible_checker->compatibleTypes(line);
    for (Block block : block_groups.at(group_name)){
        std::vector<uint16_t> compare_blocks;
        switch(line.getNormalDirection()){
            case d2kmapapi::Direction::UP:
                compare_blocks = block.getBottomTiles();
                break;
            case d2kmapapi::Direction::LEFT:
                compare_blocks = block.getRightTiles();
                break;
            case d2kmapapi::Direction::RIGHT:
                compare_blocks = block.getLeftTiles();
                break;
            case d2kmapapi::Direction::DOWN:
                compare_blocks = block.getTopTiles();
                break;
        }
        std::vector<CompatibleType> compatible_types_check = compatible_checker->compatibleTypes(DirectionalLine(compare_blocks, d2kmapapi::reverse(line.getNormalDirection())));
        if (d2kmapapi::isSubarray(compatible_types_check, compatible_types))
            compatible_blocks.push_back(block);
    }
    return compatible_blocks;
}
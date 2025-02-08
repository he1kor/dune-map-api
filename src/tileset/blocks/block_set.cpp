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

DirectionalLine Block::getDirectionalOutLine(d2kmapapi::Direction direction) const{
    switch(direction){
        case d2kmapapi::Direction::UP:
            return DirectionalLine(this->getTopTiles(), direction);
        case d2kmapapi::Direction::LEFT:
            return DirectionalLine(this->getLeftTiles(), direction);
        case d2kmapapi::Direction::RIGHT:
            return DirectionalLine(this->getRightTiles(), direction);
        case d2kmapapi::Direction::DOWN:
            return DirectionalLine(this->getBottomTiles(), direction);
    }
    throw std::invalid_argument("Unknown direction " + direction);
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

int Block::getSizeAlongDirection(d2kmapapi::Direction direction) const{
    switch (direction){
        case d2kmapapi::Direction::LEFT:
        case d2kmapapi::Direction::RIGHT:
            return getWidth();
    }
    return getHeight();
}
int Block::getSizePerpendicularToDirection(d2kmapapi::Direction direction) const{
    switch (direction){
        case d2kmapapi::Direction::LEFT:
        case d2kmapapi::Direction::RIGHT:
            return getHeight();
    }
    return getWidth();
}

BlockSet::BlockSet(const std::map<std::string, std::vector<Block>> &block_groups, CompatibleChecker *compatible_checker) : block_groups{block_groups}, compatible_checker{compatible_checker}{}

BlockSet::BlockSet(const std::map<std::string, std::vector<Block>> &block_groups) : block_groups{block_groups} {}

BlockSet::BlockSet(){}

int BlockSet::getQuickShift(const CompatibleType &compatible_type, d2kmapapi::Direction direction, const Block &block) const{
    auto reversed = d2kmapapi::reverse(direction);
    
    for (int i = 0; i < block.getDirectionalOutLine(reversed).size(); i++){
        if (compatible_checker->compatibleType(block.getDirectionalOutLine(reversed)[i], reversed) == compatible_type)
            return i;
    }
    throw std::invalid_argument("Block is not compatible to the provided compatible type!");
    return -1;
}

int BlockSet::getQuickShift(const DirectionalLine &line, const Block &block) const{
    if (block.getSizePerpendicularToDirection(line.getNormalDirection()) == line.size())
        return 0;
    auto compatible_type = compatible_checker->compatibleType(line[0], line.getNormalDirection());
    return getQuickShift(compatible_type, line.getNormalDirection(), block);
}

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

//TODO: add cache for already used blocks on such compatible types in such direction
std::vector<Block> BlockSet::compatibleBlocks(const std::vector<CompatibleType>& compatible_types, d2kmapapi::Direction direction, std::string group_name){
    checkGroupExists(group_name);

    std::vector<Block> compatible_blocks;
    for (Block block : block_groups.at(group_name)){

        auto compatible_types_check = compatible_checker->compatibleTypes(block.getDirectionalOutLine(direction));

        if (d2kmapapi::isSubarray(compatible_types_check, compatible_types))
            compatible_blocks.push_back(block);
    }
    return compatible_blocks;
}

std::vector<Block> BlockSet::compatibleBlocks(const DirectionalLine& line, std::string group_name){
    checkGroupExists(group_name);
    auto compatible_types = compatible_checker->compatibleTypes(line);
    return compatibleBlocks(compatible_types, d2kmapapi::reverse(line.getNormalDirection()), group_name);
}

bool BlockSet::checkGroupExists(std::string group_name){
    if (block_groups.count(group_name))
        return true;
    throw std::invalid_argument("Block group " + group_name + " doesn't exist!");
    return false;
}

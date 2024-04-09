#include "block_set.h"
#include <stdexcept>
#include <format>

BlockSet::BlockSet(const std::map<std::string, std::vector<Block>> &block_groups) : block_groups{block_groups}{}

BlockSet::BlockSet(){}

void BlockSet::addCompatibleCheker(const CompatibleChecker *compatible_checker){
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

std::vector<Block> BlockSet::compatibleBlocks(const DirectionalLine& line, std::string groupName){
    std::vector<Block> compatible_blocks;
    return compatible_blocks;
}
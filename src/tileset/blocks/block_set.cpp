#include "block_set.h"

BlockSet::BlockSet(const std::vector<Block> &blocks) : blocks{blocks}{}

BlockSet::BlockSet(){}

void BlockSet::addBlock(const Block &block){
    blocks.push_back(block);
}

std::vector<Block> BlockSet::compatibleBlocks(d2kmapapi::Direction direction){
    std::vector<Block> compatible_blocks;
}
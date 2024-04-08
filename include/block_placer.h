#pragma once
#include <vector>
#include <cstdint>
#include "block_set.h"
#include "map.h"
#include "edge.h"
#include "compatible_checker.h"

class BlockPlacer{
    public:
        BlockPlacer();
        void place(int x, int y, const Block& block);
        bool fit(const Edge& edge) const;
    private:
        CompatibleChecker* compatible_checker;
        BlockSet* block_set;
        Map* map;
};
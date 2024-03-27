#pragma once
#include "map.h"
#include "edge.h"
#include "compatible_checker.h"

class BlockPlacer{
    public:
        void place(int x, int y);
        void place(int x, int y, int x_offset, int y_offset);
        bool fit(const Edge& edge) const;
    private:
        CompatibleCheker* compatible_checker;
        Map* map;
};
#pragma once
#include <cstdint>
#include "tile.h"

struct LocatedTile : Tile{
    LocatedTile(Tile tile, int x, int y);
    bool operator<(const LocatedTile& lt) const;
    int x;
    int y;
};
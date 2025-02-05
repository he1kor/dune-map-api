#pragma once
#include <cstdint>
#include "tile.h"

struct LocatedTile : Tile{
    LocatedTile(uint16_t tile_id, uint16_t entity_id, int x, int y);
    LocatedTile(Tile tile, int x, int y);
    bool operator<(const LocatedTile& lt) const;
    int x = 0;
    int y = 0;
};
#include "located_tile.h"

LocatedTile::LocatedTile(Tile tile, int x, int y) : x{x}, y{y}{
    tileID = tile.tileID;
    entityID = tile.entityID;
}
#include "located_tile.h"

LocatedTile::LocatedTile(Tile tile, int x, int y) : x{x}, y{y}{
    tileID = tile.tileID;
    entityID = tile.entityID;
}

bool LocatedTile::operator<(const LocatedTile &lt) const{
    return 
        x < lt.x || 
        (x == lt.x && y < lt.y) ||
        (x == lt.x && y == lt.y && tileID < lt.tileID) ||
        (x == lt.x && y == lt.y && tileID == lt.tileID && entityID < lt.entityID);
}

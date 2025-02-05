#include "located_tile.h"

LocatedTile::LocatedTile(uint16_t tileID, uint16_t entityID, int x, int y) :
    Tile(tileID, entityID),
    x{x},
    y{y}
    {};

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

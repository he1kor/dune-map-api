#include "tileset_properties.h"

TilesetProperties::~TilesetProperties(){
    delete block_set.getCompatibleChecker();
}
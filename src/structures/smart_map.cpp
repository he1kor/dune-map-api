#include "smart_map.h"
#include <stdexcept>
#include <memory>

SmartMap::SmartMap(const SmartMap &map) :
    Map(map){}

SmartMap::SmartMap(const Map &map) :
    Map(map){}

SmartMap::SmartMap(uint16_t width, uint16_t height) :
    Map(width, height){}

SmartMap SmartMap::fromMap(const Map &map){
    return SmartMap(map);
}

void SmartMap::setHistoryStack(HistoryStack *history_stack){
    this->history_stack = history_stack;
}

HistoryStack* SmartMap::getHistoryStack(){
    return history_stack;
}

void SmartMap::initializeNewHistoryStack(){
    history_stack = new HistoryStack(this);
}

bool SmartMap::commit()
{
    if (!history_stack)
        return false;
    return this->history_stack->commit();
}
void SmartMap::setUntrackedTile(int x, int y, Tile tile){
    matrix[y][x] = tile;
}

void SmartMap::setUntrackedTileID(int x, int y, uint16_t tile_id){
    matrix[y][x].tileID = tile_id;
}

void SmartMap::setUntrackedEntityID(int x, int y, uint16_t entity_id){
    matrix[y][x].entityID = entity_id;
}

void SmartMap::setUntrackedTile(LocatedTile located_tile){
    matrix[located_tile.y][located_tile.x] = located_tile;
}

Tile SmartMap::getTile(int x, int y){
    return matrix[y][x];
}

uint16_t SmartMap::getTileID(int x, int y){
    return matrix[y][x].tileID;
}

uint16_t SmartMap::getEntityD(int x, int y){
    return matrix[y][x].entityID;
}

void SmartMap::commitTile(int x, int y, Tile tile){
    if (!history_stack){
        setUntrackedTile(x, y, tile);
        return;
    }
    history_stack->quickCommit({tile, x, y});
}
void SmartMap::commitTileID(int x, int y, uint16_t tile_id){
    if(!history_stack){
        setUntrackedTileID(x, y, tile_id);
        return;
    }
    history_stack->quickCommit(LocatedTile{
        tile_id,
        matrix[y][x].entityID,
        x,
        y
    });
}
void SmartMap::commitEntityID(int x, int y, uint16_t entity_id){
    if(!history_stack){
        setUntrackedEntityID(x, y, entity_id);
        return;
    }
    history_stack->quickCommit(LocatedTile(
        matrix[y][x].tileID,
        entity_id,
        x,
        y
    ));
}
void SmartMap::commitTile(LocatedTile located_tile)
{
    if (!history_stack){
        setUntrackedTile(located_tile);
        return;
    }
    history_stack->quickCommit(located_tile);
}

void SmartMap::addTile(int x, int y, Tile tile){
    if (!history_stack){
        setUntrackedTile(x, y, tile);
        return;
    }
    history_stack->trackChange({tile, x, y});
}

void SmartMap::addTileID(int x, int y, uint16_t tile_id){
    if (!history_stack){
        setUntrackedTileID(x, y, tile_id);
        return;
    }
    history_stack->trackChange(LocatedTile{
        tile_id,
        matrix[y][x].entityID,
        x,
        y
    });
}

void SmartMap::addEntityID(int x, int y, uint16_t entity_id){
    if (!history_stack){
        setUntrackedEntityID(x, y, entity_id);
        return;
    }
    history_stack->trackChange({
        matrix[y][x].tileID,
        entity_id,
        x,
        y
    });
}

void SmartMap::addTile(LocatedTile located_tile){
    if (!history_stack){
        setUntrackedTile(located_tile);
        return;
    }
    history_stack->trackChange(located_tile);
}

DirectionalLine SmartMap::getLineFacingEdge(const Edge &edge, const d2kmapapi::Direction &facingDirection){
    std::vector<uint16_t> edge_tiles;
    for (auto [x, y] : facingDirection == d2kmapapi::Direction::RIGHT || facingDirection == d2kmapapi::Direction::DOWN ? edge.onAfter() : edge.onBefore()){
        edge_tiles.push_back((*this)[y][x].tileID);
    }
    return DirectionalLine(edge_tiles, facingDirection);
}

Tile SmartMap::getTileByCoords(std::pair<int, int> coords){
    return (*this)[coords.first][coords.second];
}

std::vector<Tile> SmartMap::getTilesByCoords(std::vector<std::pair<int, int>> coords){
    std::vector<Tile> tiles;
    for (auto [x, y] : coords){
        tiles.push_back((*this)[y][x]);
    }
    return tiles;
}

uint16_t SmartMap::getTileIDByCoords(std::pair<int, int> coords){
    return getTileByCoords(coords).tileID;
}

std::vector<uint16_t> SmartMap::getTileIDsByCoords(std::vector<std::pair<int, int>> coords){
    std::vector<uint16_t> tiles;
    for (auto [x, y] : coords){
        tiles.push_back((*this)[y][x].tileID);
    }
    return tiles;
}

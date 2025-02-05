#pragma once

#include "map.h"
#include "history_stack.h"
#include "directional_line.h"
#include "edge.h"

class SmartMap : public Map{
public: 
    SmartMap(const SmartMap& map);
    SmartMap(uint16_t width, uint16_t height);

    static SmartMap fromMap(const Map& map);

    void setHistoryStack(HistoryStack* history_stack);
    HistoryStack* getHistoryStack();

    void initializeNewHistoryStack();
    bool commit();
    void commitTile(int x, int y, Tile tile);
    void commitTileID(int x, int y, uint16_t tile_id);
    void commitEntityID(int x, int y, uint16_t entity_id);
    void commitTile(LocatedTile located_tile);

    void addTile(int x, int y, Tile tile);
    void addTileID(int x, int y, uint16_t tile_id);
    void addEntityID(int x, int y, uint16_t entity_id);
    void addTile(LocatedTile located_tile);

    void setUntrackedTile(int x, int y, Tile tile);
    void setUntrackedTileID(int x, int y, uint16_t tile_id);
    void setUntrackedEntityID(int x, int y, uint16_t entity_id);
    void setUntrackedTile(LocatedTile located_tile);

    Tile getTile(int x, int y);
    uint16_t getTileID(int x, int y);
    uint16_t getEntityD(int x, int y);

    DirectionalLine getLineFacingEdge(const Edge& edge, const d2kmapapi::Direction& facingDirection);

    Tile getTileByCoords(std::pair<int, int> coords);
    std::vector<Tile> getTilesByCoords(std::vector<std::pair<int, int>> coords);

    uint16_t getTileIDByCoords(std::pair<int, int> coords);
    std::vector<uint16_t> getTileIDsByCoords(std::vector<std::pair<int, int>> coords);
private:
    void checkHistoryStackMap(HistoryStack* history_stack);
    SmartMap(const Map& map);
    HistoryStack* history_stack = nullptr;
    using Map::operator[];
};
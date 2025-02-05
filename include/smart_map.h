#pragma once

#include "map.h"
#include "history_stack.h"
#include "directional_line.h"
#include "edge.h"

class SmartMap : protected Map{
public: 
    SmartMap(const SmartMap& map);
    SmartMap(uint16_t width, uint16_t height);

    static SmartMap fromMap(const Map& map);

    void setHistoryStack(HistoryStack* history_stack);
    HistoryStack* getHistoryStack();

    //void apply(Tile tile, int x, int y);
    bool commit();
    void commitTile(int x, int y, Tile tile);
    void addTile(int x, int y, Tile tile);
    void setUntrackedTile(int x, int y, Tile tile);

    DirectionalLine getLineFacingEdge(const Edge& edge, const d2kmapapi::Direction& facingDirection);

    Tile getTileByCoords(std::pair<int, int> coords);
    std::vector<Tile> getTilesByCoords(std::vector<std::pair<int, int>> coords);

    uint16_t getTileIDByCoords(std::pair<int, int> coords);
    std::vector<uint16_t> getTileIDsByCoords(std::vector<std::pair<int, int>> coords);
private:
    SmartMap(const Map& map);
    HistoryStack* history_stack = nullptr;

};
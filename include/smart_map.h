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

    void apply(Tile tile, int x, int y);
    bool commit();

    DirectionalLine getLineFacingEdge(const Edge& edge, const d2kmapapi::Direction& facingDirection);

    Tile SmartMap::getTileByCoords(std::pair<int, int> coords);
    std::vector<Tile> SmartMap::getTilesByCoords(std::vector<std::pair<int, int>> coords);

    uint16_t getTileIDByCoords(std::pair<int, int> coords);
    std::vector<uint16_t> getTileIDsByCoords(std::vector<std::pair<int, int>> coords);
private:
    HistoryStack* history_stack = nullptr;
};
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
    DirectionalLine getLineFacingEdge(const Edge& edge, const d2kmapapi::Direction& facingDirection);
private:
    HistoryStack* history_stack;
};
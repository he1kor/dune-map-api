#include "smart_map.h"

SmartMap::SmartMap(const SmartMap &map) : Map(map){}

SmartMap::SmartMap(uint16_t width, uint16_t height) : Map(width, height) {}

SmartMap SmartMap::fromMap(const Map &map){
    return SmartMap(map.width(), map.height());
}

void SmartMap::setHistoryStack(HistoryStack *history_stack){
    this->history_stack = history_stack;
}

DirectionalLine SmartMap::getLineFacingEdge(const Edge &edge, const d2kmapapi::Direction &facingDirection){
    std::vector<uint16_t> edge_tiles;
    for (auto [x, y] : facingDirection == d2kmapapi::Direction::RIGHT || facingDirection == d2kmapapi::Direction::DOWN ? edge.onAfter() : edge.onBefore()){
        edge_tiles.push_back((*this)[y][x].tileID);
    }
    return DirectionalLine(edge_tiles, facingDirection);
}

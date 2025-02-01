#include "smart_map.h"
#include <stdexcept>

SmartMap::SmartMap(const SmartMap &map) : Map(map){}

SmartMap::SmartMap(uint16_t width, uint16_t height) : Map(width, height) {}

SmartMap SmartMap::fromMap(const Map &map){
    return SmartMap(map.width(), map.height());
}

void SmartMap::setHistoryStack(HistoryStack *history_stack){
    this->history_stack = history_stack;
}

bool SmartMap::commit(){
    if (!history_stack)
        throw std::runtime_error("History stack is not initialized.");
    return this->history_stack->commit();
}

DirectionalLine SmartMap::getLineFacingEdge(const Edge &edge, const d2kmapapi::Direction &facingDirection)
{
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

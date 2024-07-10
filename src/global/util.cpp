#include "util.h"

d2kmapapi::Direction d2kmapapi::reverse(Direction direction){
    return Direction(3-direction);
}
std::vector<uint16_t> d2kmapapi::getTilesbyCoords(Map& map, std::vector<std::pair<int, int>> coords){
    std::vector<uint16_t> tiles;
    for (auto [x, y] : coords){
        tiles.push_back(map[y][x].tileID);
    }
    return tiles;
}
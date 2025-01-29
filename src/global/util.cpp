#include "util.h"
#include <random>

d2kmapapi::Direction d2kmapapi::reverse(Direction direction){
    return Direction(3-direction);
}
int d2kmapapi::getRandomNumber(int begin, int end){

    static std::random_device seed;
    static std::mt19937 gen(seed());
    static std::uniform_int_distribution<> distrib(begin, end);

    return distrib(gen);
}
int d2kmapapi::getRandomNumberOld(int begin, int end){
    int range = end - begin + 1;
    return rand() % range + begin;
}
std::vector<uint16_t> d2kmapapi::getTilesbyCoords(Map &map, std::vector<std::pair<int, int>> coords)
{
    std::vector<uint16_t> tiles;
    for (auto [x, y] : coords){
        tiles.push_back(map[y][x].tileID);
    }
    return tiles;
}
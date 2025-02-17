#include "util.h"
#include <random>
#include <cmath>

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

int d2kmapapi::getManhattanDistance(int x1, int y1, int x2, int y2){
    return abs(x2 - x1) + abs(y2 - y1);
}
namespace d2kmapapi{
    extern const std::set<d2kmapapi::Direction> directions = {d2kmapapi::Direction::DOWN, d2kmapapi::Direction::LEFT, d2kmapapi::Direction::RIGHT, d2kmapapi::Direction::UP};
}

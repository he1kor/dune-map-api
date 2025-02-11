#include "wall.h"

Wall::Wall(){}

Wall::Wall(int width, int height) : width{width}, height{height}, segments(height, std::vector<WallSegment>(width, NONE)){}
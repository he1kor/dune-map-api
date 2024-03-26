#include "edge.h"
#include <stdexcept>
#include <format>
#include "global.h"

Edge::Edge(int x, int y, int size, Orientation orientation) : x{x}, y{y}, size{size}, orientation{orientation} {};

bool Edge::checkLeftBounds(int x){
    if (x < 0)
        throw std::out_of_range(std::format("Left edge! ({})", 0));
}
bool Edge::checkRightBounds(int x){
    if (x > d2kmapapi::max_map_size)
        throw std::out_of_range(std::format("Right edge! ({})", d2kmapapi::max_map_size));
}

bool Edge::checkTopBounds(int y){
    if (y < 0)
        throw std::out_of_range(std::format("Top edge! ({})", 0));
}

bool Edge::checkBottomBounds(int y){
    if (y > d2kmapapi::max_map_size)
        throw std::out_of_range(std::format("Bottom edge! ({})", d2kmapapi::max_map_size));
}




Horizontal::Horizontal(int x, int y, int size) : Edge::Edge(x, y, size, Orientation::horizontal){}

Horizontal Horizontal::fromTop(int x, int y){
    checkTopBounds(y+1);
    checkBottomBounds(y+1);
    checkLeftBounds(x);
    checkRightBounds(x);
    return Horizontal(x, y+1, 1);
}

Horizontal Horizontal::fromTop(int x1, int x2, int y){
    checkTopBounds(y+1);
    checkBottomBounds(y+1);
    checkLeftBounds(x1);
    checkRightBounds(x2);
    if (x2 < x1)
        throw std::invalid_argument(std::format("The x2 ({}) should not be less than x1 ({})!", x1, x2));
    return Horizontal(x1, y+1, 1+x2-x1);
}

Horizontal Horizontal::fromBottom(int x, int y){
    checkTopBounds(y);
    checkBottomBounds(y);
    checkLeftBounds(x);
    checkRightBounds(x);
    return Horizontal(x, y, 1);
}

Horizontal Horizontal::fromBottom(int x1, int x2, int y){
    checkTopBounds(y);
    checkBottomBounds(y);
    checkLeftBounds(x1);
    checkRightBounds(x2);
    if (x2 < x1)
        throw std::invalid_argument(std::format("The x2 ({}) should not be less than x1 ({})!", x1, x2));
    return Horizontal(x1, y, 1+x2-x1);
}





Vertical::Vertical(int x, int y, int size) : Edge::Edge(x, y, size, Orientation::vertical){}


Vertical Vertical::fromLeft(int x, int y){
    checkTopBounds(y);
    checkBottomBounds(y);
    checkLeftBounds(x+1);
    checkRightBounds(x+1);
    return Vertical(x+1, y, 1);
}
Vertical Vertical::fromLeft(int y1, int y2, int x){
    checkTopBounds(y1);
    checkBottomBounds(y2);
    checkLeftBounds(x+1);
    checkRightBounds(x+1);
    if (y2 < y1)
        throw std::invalid_argument(std::format("The y2 ({}) should not be less than y1 ({})!", y1, y2));
    return Vertical(x+1, y1, 1+y2-y1);
}


Vertical Vertical::fromRight(int x, int y){
    checkTopBounds(y);
    checkBottomBounds(y);
    checkLeftBounds(x);
    checkRightBounds(x);
    return Vertical(x, y, 1);
}
Vertical Vertical::fromRight(int y1, int y2, int x){
    checkTopBounds(y1);
    checkBottomBounds(y2);
    checkLeftBounds(x);
    checkRightBounds(x);
    if (y2 < y1)
        throw std::invalid_argument(std::format("The y2 ({}) should not be less than y1 ({})!", y1, y2));
    return Vertical(x, y1, 1+y2-y1);
}

std::vector<std::pair<int, int>> Vertical::onLeft(){
    checkLeftBounds(x-1);
    std::vector<std::pair<int, int>> tiles(size);
    for (int i_y = y; i_y < y+size; i_y++){
        tiles.push_back({x-1, i_y});
    }
    return tiles;
}

std::pair<int, int> Vertical::onLeft(int i){
    checkLeftBounds(x-1);
    if (i < 0 || i >= size)
        throw std::out_of_range(std::format("The i ({}) is out of range!", i));
    return {x-1, y+i};
}
std::vector<std::pair<int, int>> Vertical::onRight(){
    checkRightBounds(x+1);
    std::vector<std::pair<int, int>> tiles(size);
    for (int i_y = y; i_y < y+size; i_y++){
        tiles.push_back({x, i_y});
    }
    return tiles;
}

std::pair<int, int> Vertical::onRight(int i){
    checkRightBounds(x+1);
    if (i < 0 || i >= size)
        throw std::out_of_range(std::format("The i ({}) is out of range!", i));
    return {x, y+i};
}

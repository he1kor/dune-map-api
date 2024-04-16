#include "edge.h"
#include <stdexcept>
#include <format>
#include "global.h"

//horizontal line is above the same Y tile      (top  tile is Y-1, bottom tile is Y)
//vertical   line is on left of the same X tile (left tile is X-1, right  tile is X)

Edge::Edge(int x, int y, int size, Orientation orientation) : x{x}, y{y}, size{size}, orientation{orientation} {
    if (size < 1)
        throw std::invalid_argument(std::format("The size ({}) should not be less than 1!", size));
    if (x < 0 ||
        y < 0 ||
        x + size-1 > d2kmapapi::max_map_size ||
        y + size-1 > d2kmapapi::max_map_size)
        throw std::out_of_range(std::format("The coords ({}-{},{}-{}) are out of map bounds ({})!", x, x+size-1, y, y+size-1, d2kmapapi::max_map_size));
};

std::vector<std::pair<int, int>> Edge::onBefore() const{
    std::vector<std::pair<int, int>> tiles(size);
    if (orientation == Orientation::horizontal){
        checkTopBounds(y);
        for (int i_x = x; i_x < x+size; i_x++){
            tiles.push_back({i_x, y-1});
        }
    } else {
        checkLeftBounds(x);
        for (int i_y = y; i_y < y+size; i_y++){
            tiles.push_back({x-1, i_y});
        }
    }
    return tiles;
}
std::pair<int, int> Edge::onBefore(int i) const{
    if (orientation == Orientation::horizontal){
        checkTopBounds(y);
        if (i < 0 || i >= size)
            throw std::out_of_range(std::format("The i ({}) is out of range!", i));
        return {x+i, y-1};
    } else {
        checkLeftBounds(x);
        if (i < 0 || i >= size)
            throw std::out_of_range(std::format("The i ({}) is out of range!", i));
        return {x-1, y+i};
    }
}
std::vector<std::pair<int, int>> Edge::onAfter() const{
    std::vector<std::pair<int, int>> tiles(size);
    if (orientation == Orientation::horizontal){
        checkBottomBounds(y);
        for (int i_x = x; i_x < x+size; i_x++){
            tiles.push_back({i_x, y});
        }
    } else {
        checkRightBounds(x);
        for (int i_y = y; i_y < y+size; i_y++){
            tiles.push_back({x, i_y});
        }
    }
    return tiles;
}
std::pair<int, int> Edge::onAfter(int i) const{
    if (orientation == Orientation::horizontal){
        checkBottomBounds(y);
        if (i < 0 || i >= size)
            throw std::out_of_range(std::format("The i ({}) is out of range!", i));
        return {x+i, y};
    } else {
        checkRightBounds(x);
        if (i < 0 || i >= size)
            throw std::out_of_range(std::format("The i ({}) is out of range!", i));
        return {x, y+i};
    }
}

int Edge::getX() const{
    return x;
}
int Edge::getY() const{
    return y;
}
int Edge::getSize() const{
    return size;
}
Orientation Edge::getOrientation() const{
    return orientation;
}


bool Edge::checkLeftBounds(int edge_x){
    if (edge_x <= 0){
        throw std::out_of_range(std::format("Left edge! ({})", 0));
        return false;
    }
    return true;
}
bool Edge::checkRightBounds(int edge_x){
    if (edge_x >= d2kmapapi::max_map_size){
        throw std::out_of_range(std::format("Right edge! ({})", d2kmapapi::max_map_size));
        return false;
    }
    return true;
}

bool Edge::checkTopBounds(int edge_y){
    if (edge_y <= 0){
        throw std::out_of_range(std::format("Top edge! ({})", 0));
        return false;
    }
    return true;
}

bool Edge::checkBottomBounds(int edge_y){
    if (edge_y >= d2kmapapi::max_map_size){
        throw std::out_of_range(std::format("Bottom edge! ({})", d2kmapapi::max_map_size));
        return false;
    }
    return true;
}


Horizontal::Horizontal(int x, int y, int size) : Edge::Edge(x, y, size, Orientation::horizontal){}

Horizontal Horizontal::fromTop(int x, int y){
    return Horizontal(x, y+1, 1);
}

Horizontal Horizontal::fromTop(int x1, int x2, int y){
    if (x2 < x1)
        throw std::invalid_argument(std::format("The x2 ({}) should not be less than x1 ({})!", x1, x2));
    return Horizontal(x1, y+1, 1+x2-x1);
}

Horizontal Horizontal::fromBottom(int x, int y){
    return Horizontal(x, y, 1);
}

Horizontal Horizontal::fromBottom(int x1, int x2, int y){
    if (x2 < x1)
        throw std::invalid_argument(std::format("The x2 ({}) should not be less than x1 ({})!", x1, x2));
    return Horizontal(x1, y, 1+x2-x1);
}

std::vector<std::pair<int, int>> Horizontal::onTop(){
    return onBefore();
}

std::pair<int, int> Horizontal::onTop(int i){
    return onBefore(i);
}

std::vector<std::pair<int, int>> Horizontal::onBottom(){
    return onAfter();
}

std::pair<int, int> Horizontal::onBottom(int i){
    checkBottomBounds(y);
    if (i < 0 || i >= size)
        throw std::out_of_range(std::format("The i ({}) is out of range!", i));
    return {x+i, y};
}

Vertical::Vertical(int x, int y, int size) : Edge::Edge(x, y, size, Orientation::vertical){}


Vertical Vertical::fromLeft(int x, int y){
    return Vertical(x+1, y, 1);
}
Vertical Vertical::fromLeft(int y1, int y2, int x){
    if (y2 < y1)
        throw std::invalid_argument(std::format("The y2 ({}) should not be less than y1 ({})!", y1, y2));
    return Vertical(x+1, y1, 1+y2-y1);
}


Vertical Vertical::fromRight(int x, int y){
    return Vertical(x, y, 1);
}
Vertical Vertical::fromRight(int y1, int y2, int x){
    if (y2 < y1)
        throw std::invalid_argument(std::format("The y2 ({}) should not be less than y1 ({})!", y1, y2));
    return Vertical(x, y1, 1+y2-y1);
}

std::vector<std::pair<int, int>> Vertical::onLeft(){
    return onBefore();
}

std::pair<int, int> Vertical::onLeft(int i){
    return onBefore(i);
}
std::vector<std::pair<int, int>> Vertical::onRight(){
    return onAfter();
}

std::pair<int, int> Vertical::onRight(int i){
    return onAfter(i);
}

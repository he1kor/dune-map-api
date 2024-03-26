#include "edge.h"
#include <stdexcept>
#include <format>

Edge::Edge(int x, int y, int size, Orientation orientation) : x{x}, y{y}, size{size}, orientation{orientation} {};

Horizontal::Horizontal(int x, int y, int size) : Edge::Edge(x, y, size, Orientation::horizontal){}

Horizontal Horizontal::fromTop(int x, int y){
    return Horizontal(x, y, 1);
}

Horizontal Horizontal::fromTop(int x1, int x2, int y){
    if (x2 < x1)
        throw std::invalid_argument(std::format("The x2 ({}) should not be less than x1 ({})!", x1, x2));
    return Horizontal(x1, y, 1+x2-x1);
}

Horizontal Horizontal::fromBottom(int x, int y){
    return Horizontal(x+1, y+1, 1);
}

Horizontal Horizontal::fromBottom(int x1, int x2, int y){
    if (x2 < x1)
        throw std::invalid_argument(std::format("The x2 ({}) should not be less than x1 ({})!", x1, x2));
    return Horizontal(x1+1, y+1, 1+x2-x1);
}

Vertical::Vertical(int x, int y, int size) : Edge::Edge(x, y, size, Orientation::vertical){}

Vertical Vertical::fromLeft(int x, int y){
    return Vertical(x, y, 1);
}

Vertical Vertical::fromLeft(int x1, int x2, int y){
    if (x2 < x1)
        throw std::invalid_argument(std::format("The x2 ({}) should not be less than x1 ({})!", x1, x2));
    return Vertical(x1, y, 1+x2-x1);
}

Vertical Vertical::fromRight(int x, int y){
    return Vertical(x+1, y+1, 1);
}

Vertical Vertical::fromRight(int x1, int x2, int y){
    if (x2 < x1)
        throw std::invalid_argument(std::format("The x2 ({}) should not be less than x1 ({})!", x1, x2));
    return Vertical(x1+1, y+1, 1+x2-x1);
}

std::vector<std::pair<int, int>> Vertical::onLeft(){
    std::vector<std::pair<int, int>> tiles(size);
    for (int i_y = y; i_y < y+size; i_y++){
        tiles.push_back({x-1, i_y});
    }
    return tiles;
}

std::pair<int, int> Vertical::onLeft(int i){
    return {x, y};
}
std::vector<std::pair<int, int>> Vertical::onRight(){
    std::vector<std::pair<int, int>> tiles(size);
    for (int i_y = y; i_y < y+size; i_y++){
        tiles.push_back({x, i_y});
    }
    return tiles;
}

std::pair<int, int> Vertical::onRight(int i){
    return {x, y};
}

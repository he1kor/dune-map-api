#include "map.h"
#include <stdexcept>
#include <iostream>

const uint16_t Map::MAX_WIDTH = 128;
const uint16_t Map::MAX_HEIGHT = 128;

Row::Row(){}
Row::Row(uint16_t size) : 
    _size(size),
    tiles(new Tile[size]){
    };

Tile& Row::operator[](uint16_t index){
    if (index < 0 || index >= _size){
        throw std::out_of_range(index + " is out of " + _size);
    } 
    return tiles[index];
}

uint16_t Row::size(){
    return _size;
}




Map::Map(uint16_t width, uint16_t height) : 
    _width(width),
    _height(height)
{
    validateSize(width, height);
    matrix = new Row[height];
    for (int i = 0; i < height; i++) {
        matrix[i] = Row(width);
    }
}

Row& Map::operator[](uint16_t index){
    if (index < 0 || index >= _height){
        throw std::out_of_range(index + " is out of " + _height);
    } 
    return matrix[index];
};

uint16_t Map::width(){
    return _width;
}

uint16_t Map::height(){
    return _height;
}

bool Map::validateSize(uint16_t width, uint16_t height){
    if (width % 2 == 1){
        throw std::runtime_error("Width should be even number");
        return 1;
    }
    
    if (height % 2 == 1){
        throw std::runtime_error("Height should be even number");
        return 1;
    }
    if (width > MAX_WIDTH || width < 0){
        throw std::runtime_error("Width is out of 0.." + MAX_WIDTH);
        return 1;
    }
    if (height > MAX_HEIGHT || width < 0){
        throw std::runtime_error("Height is out of 0.." + MAX_HEIGHT);
        return 1;
    }
    return 0;
}

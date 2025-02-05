#include "map.h"
#include <stdexcept>
#include <algorithm>

const uint16_t Map::MAX_WIDTH = 128;
const uint16_t Map::MAX_HEIGHT = 128;

Row::Row(){}
Row::Row(uint16_t size) : 
    _size(size), tiles(size){
};
Row::Row(const Row& row) : _size(row._size), tiles(row.tiles){}

Row& Row::operator=(Row row){
    std::swap(this->_size, row._size);
    std::swap(this->tiles, row.tiles);
    return *this;
}


Tile& Row::operator[](uint16_t index){
    return tiles.at(index);
}

const Tile &Row::operator[](uint16_t index) const{
    return this->tiles.at(index);
}

uint16_t Row::size() const{
    return _size;
}

Map::Map(){}

Map::Map(uint16_t width, uint16_t height){
    validateSize(width, height);
    _width = width;
    _height = height;
    matrix = std::vector<Row>(height, Row(width));
}

Map::Map(const Map &map) : _width(map._width), _height(map._height), matrix(map.matrix){}

Map &Map::operator=(Map map){
    std::swap(this->_width, map._width);
    std::swap(this->_height, map._height);
    std::swap(this->matrix, map.matrix);
    return *this;
}

Row& Map::operator[](uint16_t index){
    if (index < 0 || index >= _height){
        throw std::out_of_range(index + " is out of " + _height);
    } 
    return matrix[index];
};

uint16_t Map::width() const{
    return _width;
}

uint16_t Map::height() const{
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

#include "map.h"
#include <stdexcept>
#include <algorithm>

const uint16_t Map::MAX_WIDTH = 128;
const uint16_t Map::MAX_HEIGHT = 128;

Row::Row(){}
Row::Row(uint16_t size) : 
    _size(size){
    tiles.reserve(size);
    std::generate_n(std::back_inserter(tiles), size, [] {
        return std::make_unique<Tile>();
    });  
};
Row::Row(const Row& row) : _size(row._size){
    tiles.reserve(row.tiles.size());
    for (auto& tile_ptr : row.tiles){
        tiles.push_back(std::make_unique<Tile>(*tile_ptr));
    }
}

Row& Row::operator=(Row row){
    std::swap(this->_size, row._size);
    std::swap(this->tiles, row.tiles);
    return *this;
}


Tile& Row::operator[](uint16_t index){
    return *(this->tiles.at(index));
}

const Tile &Row::operator[](uint16_t index) const{
    return *(this->tiles.at(index));
}

uint16_t Row::size() const{
    return _size;
}

Map::Map(){}

Map::Map(uint16_t width, uint16_t height) : 
    _width(width),
    _height(height){
    validateSize(width, height);
    matrix.reserve(height);
    std::generate_n(std::back_inserter(matrix), height, [width] {
        return std::make_unique<Row>(width);
    });
}

Map::Map(const Map &map) : _width(map._width), _height(map._height){
    matrix.reserve(map.matrix.size());
    for (auto& row_ptr : map.matrix){
        matrix.push_back(std::make_unique<Row>(*row_ptr));
    }
}

Map &Map::operator=(Map map){
    std::swap(this->_width, map._width);
    std::swap(this->_height, map._height);
    return *this;
}

Row& Map::operator[](uint16_t index){
    if (index < 0 || index >= _height){
        throw std::out_of_range(index + " is out of " + _height);
    } 
    return *(matrix[index]);
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

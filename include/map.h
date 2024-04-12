#pragma once

#include <cstdint>
#include "tile.h"

/*!
	\brief Class wrapping a row of the map.
*/
class Row{
    public:
        Row();
        Row(uint16_t size);
        Tile& operator[](uint16_t index);
        uint16_t size();
    private:
        uint16_t _size;
        Tile * tiles;
};

/*!
	\brief Class representing the whole map which can be saved. Contains matrix of Tile. Each tile is tile texture id and entity id on it.
*/
class Map{
    public:
        Map(uint16_t width, uint16_t height);
        uint16_t width();
        uint16_t height();
        Row& operator[](uint16_t index);
        static const uint16_t MAX_WIDTH;
        static const uint16_t MAX_HEIGHT;

    private:
        bool validateSize(uint16_t width, uint16_t height);
        uint16_t _width;
        uint16_t _height;
        Row* matrix;
};
#pragma once

#include <cstdint>
#include "tile.h"

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
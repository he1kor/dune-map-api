#pragma once

#include <cstdint>
#include <vector>
#include "tile.h"
#include <memory>

/*!
	\brief Class wrapping a row of the map.
*/
class Row{
    public:
        /**
         * \brief Default constructor. Size is 0, tiles are undefined.
        */
        Row();
        /**
         * \brief Common constructor, size is set from param.
         * \param size Sets size and initializes with it array.
        */
        Row(uint16_t size);
        /**
         * \brief Accesses i-th tile of the row. If out of size, it throws an exception.
         * \param index Index of the tile in the row.
         * \return Tile reference.
        */
        Tile& operator[](uint16_t index);
        /**
         * \brief Accesses i-th tile of the row constantly. If out of size, it throws an exception.
         * \param index Index of the tile in the row.
         * \return Const tile reference.
        */
        const Tile& operator[](uint16_t index) const;
        /**
         * \brief Size getter.
         * \return Size of the row.
        */
        uint16_t size();
    private:
        uint16_t _size = 0;
        std::vector<std::unique_ptr<Tile>> tiles;
};

/*!
	\brief Class representing the whole map which can be saved. Contains matrix of Tile. Each tile is tile texture id and entity id on it.
*/
class Map{
    public:
        /**
         * \brief Default constructor. Size is 0, rows are undefined.
        */
        Map();
        /**
         * \brief Constructor of the map with given width and height.
         * \param width Sets width of the map.
         * \param height Sets height of the map.
        */
        Map(uint16_t width, uint16_t height);
        
        /**
         * \brief Width getter.
         * \return Width of the map
        */
        uint16_t width() const;
        
        /**
         * \brief Height getter.
         * \return Height of the map
        */
        uint16_t height() const;
        
        /**
         * \brief Accesses i-th row of the map. If out of size, it throws an exception.
         * \param index Index of the row in the map.
         * \return Row reference.
        */
        virtual Row& operator[](uint16_t index);
        static const uint16_t MAX_WIDTH;
        static const uint16_t MAX_HEIGHT;

    private:
        bool validateSize(uint16_t width, uint16_t height);
        uint16_t _width;
        uint16_t _height;
        Row* matrix;
};
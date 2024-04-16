#pragma once
#include <cstdint>
#include <set>
#include <vector>

/*!
	\brief Class representing functionally the same plain tiles but with different texture. 
*/
class Material{
    public:
        /**
         * \brief Default constructor. Arrays are remained empty.
        */
        Material();

        /**
         * \brief Single-tile constructor. Constructcs Material from one only tile.
        */
        Material(uint16_t tile);

        /**
         * \brief Tileset-based constructor. Constructcs Material from IDs in the rectangle block of tiles in tileset with tileset_width assumed from the global.h
         * \param x X of top-left corner of the tile rectangle in the tileset.
         * \param x Y of top-left corner of the tile rectangle in the tileset.
         * \param width Width of the rectangle in the tileset.
         * \param height height of the rectangle in the tileset.
        */
        Material(int x, int y, int width, int height);
        
        /**
         * \brief Returns whether material contains provided tile with o(log(n)) time complexity.
         * \param tile Expected tile to be in the Material.
         * \return Whether material contains provided tile.
        */
        bool containsTile(uint16_t tile) const;

        /**
         * \brief Getter for the i-th tile in the material. Throws exception if i is out of bounds.
         * \param i Index of the tile to return.
         * \return i-th tile id of the material.
        */
        const uint16_t& operator[](int i) const;

        /**
         * \brief Adds a given tile to the Material.
         * \param tile Tile id to put in.
        */
        void addTile(uint16_t tile);

        /**
         * \brief Equals operator. Materials are equal if they're the same size and contain the same tiles in any order.
        */
        bool operator==(const Material& other) const;

        /**
         * \brief Size getter.
         * \return Count of the tiles in the Material.
        */
        int size() const;
    private:
        std::vector<uint16_t> indexed_tiles;
        std::set<uint16_t> set_tiles;
};
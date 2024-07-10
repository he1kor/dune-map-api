#pragma once
#include <vector>
#include <cstdint>
#include "util.h"
/*!
	\brief Wrapper of tiles array and normal direction of this array, used for simplifying compatible algorithms code.
*/
class DirectionalLine{
    public:
        /**
         * \brief Common constructor. Takes tile array and normal direction.
         * \param tiles Tile array.
         * \param normal_direction Normal direction.
        */
        DirectionalLine(const std::vector<uint16_t>& tiles, d2kmapapi::Direction normal_direction);
        /**
         * \brief Reverses normal direction to opposite.
        */
        void reverse();
        /**
         * \brief Tiles size getter.
         * \return number of tiles.
        */
        int size() const;
        /**
         * \brief Getter for certain tile of tiles.
         * \param i index of tile in array.
         * \return i-th tile id in the tiles.
        */
        uint16_t operator[](int i) const;
        /**
         * \brief normal_direction getter.
         * \return this normal_direction.
        */
        d2kmapapi::Direction getNormalDirection() const;
        /**
         * \brief tiles getter.
         * \return this tiles.
        */
        std::vector<uint16_t> getTiles() const;
    private:
        std::vector<uint16_t> tiles;
        d2kmapapi::Direction normal_direction;
};  
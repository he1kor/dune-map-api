/**
 * \file
 * \brief Contains all util functions in d2kmapapi namespace which used in the library.
 * 
*/
#pragma once
#include <vector>
#include "map.h"

namespace d2kmapapi{
    /**
     * \brief Used for pointing directiong from a tile.
    */
    enum Direction {
        UP = 0,
        LEFT = 1,
        RIGHT = 2,
        DOWN = 3
    };
    enum EdgeDirection {
        BEFORE = 0,
        AFTER = 1
    };
    
    /**
     * \brief Returns reversed given direction.
     * \param direction Direction to be reversed.
     * \return Reversed direction.
    */
    Direction reverse(Direction direction);

    int getRandomNumber(int begin, int end);
    int getRandomNumberOld(int begin, int end);

    std::vector<uint16_t> getTilesbyCoords(Map &map, std::vector<std::pair<int, int>> coords);

    /**
     * \brief returns True if subarray is contigous array contained in array, else returns False.
     * \param array Array which possibly contains subarray
     * \param subarray Array which is possibly subarray of previous array
     * \return True if subarray is actually subarray of array, else False
    */
    template <typename T> bool isSubarray(std::vector<T> array, std::vector<T> subarray){
        if (array.size() < subarray.size())
            return false;
        for (int i = 0; i <= array.size()-subarray.size(); i++) {
            int j;
            for (j = 0; j < subarray.size(); j++) {
                if (array[i+j] != subarray[j]) {
                    break;
                }
            }
            if (j == subarray.size()) {
                return true;
            }
        }
        return false;
    }
}
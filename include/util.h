/**
 * \file
 * \brief Contains all util functions in d2kmapapi namespace which used in the library.
 * 
*/
#pragma once
#include <vector>

namespace d2kmapapi{
    /**
     * \brief Used for pointing directiong from a tile.
    */
    enum Direction {
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3
    };
    /**
     * \brief Returns reversed given direction.
     * \param direction Direction to be reversed.
     * \return Reversed direction.
    */
    Direction reverse(Direction direction);
    /**
     * \brief returns True if subarray is contigous array contained in array, else returns False.
     * \param array Array which possibly contains subarray
     * \param subarray Array which is possibly subarray of previous array
     * \return True if subarray is actually subarray of array, else False
    */
    template <typename T> bool isSubarray(std::vector<T> array, std::vector<T> subarray){
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
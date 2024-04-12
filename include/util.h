#pragma once
#include <vector>

namespace d2kmapapi{
    enum Direction {
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3
    };
    Direction reverse(Direction direction);
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
#include "util.h"

d2kmapapi::Direction d2kmapapi::reverse(Direction direction){
    return Direction(3-direction);
}
template <typename T>
bool d2kmapapi::isSubarray(std::vector<T> array, std::vector<T> subarray){
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
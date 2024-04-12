#include "util.h"

d2kmapapi::Direction d2kmapapi::reverse(Direction direction){
    return Direction(3-direction);
}
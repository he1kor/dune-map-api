#pragma once

#include <vector>
#include "priority_map.h"

template <typename T>
class Wall{
    public:
        Wall();
        Wall(int width, int height);
        

    private:
        int width = 0;
        int height = 0;
        PriorityMap<T> priority_map;
        std::vector<std::vector<T>> segments;
};
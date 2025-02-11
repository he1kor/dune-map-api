#pragma once

#include <vector>
#include "priority_map.h"

static const int NO_NUMBER = -1;

template <typename T>
class Wall{
    private:
        int width = 0;
        int height = 0;
        PriorityMap<T> priority_map;
        std::vector<std::vector<T>> pattern;

        std::vector<std::vector<int>> numbering;
        std::vector<std::vector<T>> segments;
    public:
        Wall(int width, int height, std::vector<std::vector<T>> pattern, PriorityMap<T> priority_map) :
            width(width),
            height(height),
            pattern{pattern},
            numbering{std::vector(height, std::vector(width, NO_NUMBER))},
            segments{std::vector(height, std::vector<T>(height))},
            priority_map{priority_map}
            {}
};

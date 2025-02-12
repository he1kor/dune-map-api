#pragma once

#include <vector>
#include <exception>
#include "priority_map.h"
#include "wall_pattern.h"

static const int NO_NUMBER = -1;

template <typename T>
class Wall{
    public:
        Wall(int width, int height, PriorityMap<T> priority_map) :
            Wall(width,
                height,
                priority_map,
                WallPattern<T>(width, height),
                std::vector(0, std::vector<int>(0), 0, 0))
                {}
        Wall(int width, int height, PriorityMap<T> priority_map, WallPattern<T> pattern, int x_offset, int y_offset) :
            width(width),
            height(height),
            priority_map{priority_map},
            pattern{pattern},
            numbering{std::vector(height, std::vector(width, NO_NUMBER))},
            segments{std::vector(height, std::vector<T>(height))}
            {}
        void setPattern(WallPattern<T> pattern){
            this->pattern = pattern;
        }
        void join(int x, int y){
            if (pattern.size() == 0)
                throw std::runtime_error("Segment is not set");
        }
    private:
        int width = 0;
        int height = 0;
        PriorityMap<T> priority_map;
        WallPattern<T> pattern;
    
        std::vector<std::vector<int>> numbering;
        std::vector<std::vector<T>> segments;
};

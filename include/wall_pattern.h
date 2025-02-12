#pragma once

#include <vector>

template <typename T>
class WallPattern{
    public:
        WallPattern(std::vector<std::vector<T>> pattern, int x_offset, int y_offset) : pattern(pattern), x_offset(x_offset), y_offset(y_offset), width(pattern.at(0).size()), height(pattern.size()) {};

        WallPattern(std::vector<std::vector<T>> pattern) : 
            WallPattern(
                pattern,
                pattern.at(0).size() / 2,
                pattern.size() / 2)
            {};

        WallPattern(int width, int height, int x_offset, int y_offset) :
            WallPattern(
                std::vector(height, std::vector<T>(width)),
                x_offset,
                y_offset)
            {};
            
        WallPattern(int width, int height) : 
            WallPattern(
                std::vector(height, std::vector<T>(width))) 
            {};

        void setSegment(int x, int y, T t){
            pattern.at(y).at(x) = t;    
        }
        T getSegment(int x, int y) const {
            return pattern.at(y).at(x);
        };
    private:
        std::vector<std::vector<T>> pattern;
        int width = 0;
        int height = 0;
        int x_offset = 0;
        int y_offset = 0;
};
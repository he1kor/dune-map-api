#pragma once

#include <vector>

template <typename T>
class WallPattern{
    public:
        WallPattern(int width, int height) : WallPattern(pattern(height, vector<T>(width))) {};
        WallPattern(int width, int height, int x_offset, int y_offset) : pattern(height, vector<T>(width)), x_offset(x_offset), y_offset(y_offset) {};
        WallPattern(std::vector<std::vector<T>> pattern, int x_offset, int y_offset) : pattern(pattern), x_offset(x_offset), y_offset(y_offset) {};
        WallPattern(std::vector<std::vector<T>> pattern) : pattern(pattern), x_offset(pattern.at(0).size() / 2), y_offset(pattern.size() / 2) {};
        void setSegment(int x, int y, T t){
            pattern.at(y).at(x) = t;
        }
        T getSegment(int x, int y) const {
            return pattern.at(y).at(x);
        };
    private:
        std::vector<std::vector<T>> pattern;
        int x_offset = 0;
        int y_offset = 0;
};
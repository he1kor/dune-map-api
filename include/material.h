#pragma once
#include <cstdint>
#include <vector>

class Material{
    public:
        Material();
        Material(int x, int y, int width, int height);
        const uint16_t& operator[](int i);
        int size();
    private:
        std::vector<uint16_t> tiles;
};
#pragma once
#include <cstdint>
#include <vector>

class Material{
    public:
        Material();
        Material(uint16_t tile);
        Material(int x, int y, int width, int height);
        bool containsTile(uint16_t tile) const;
        const uint16_t& operator[](int i);
        void addTile(uint16_t tile);
        bool operator==(const Material& other) const;
        int size() const;
    private:
        std::vector<uint16_t> tiles;
};
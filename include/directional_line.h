#pragma once
#include <vector>
#include <cstdint>
#include "util.h"

class DirectionalLine{
    public:
        DirectionalLine(const std::vector<uint16_t>& tiles, d2kmapapi::Direction normal_direction);
        void reverse();
        int size() const;
        uint16_t operator[](int i) const;
        d2kmapapi::Direction getNormalDirection() const;
        std::vector<uint16_t> getTiles() const;
    private:
        std::vector<uint16_t> tiles;
        d2kmapapi::Direction normal_direction;
};
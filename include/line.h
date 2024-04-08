#pragma once
#include <vector>
#include <cstdint>
#include "util.h"

class DirectionalLine{
    public:
        DirectionalLine(std::vector<uint16_t> lines, d2kmapapi::Direction normal_direction);
        void reverse();
        std::vector<uint16_t> lines;
        int size();
        uint16_t operator[](int i);
        d2kmapapi::Direction getNormalDirection();
    private:
        std::vector<uint16_t> lines;
        d2kmapapi::Direction normal_direction;
};
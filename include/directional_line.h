#pragma once
#include <vector>
#include <cstdint>
#include "util.h"
/*!
	\brief Wrapper of tiles array and normal direction of this array, used for simplifying compatible algorithms code.
*/
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
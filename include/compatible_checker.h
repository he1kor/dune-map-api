#pragma once
#include <set>
#include <string>
#include <array>
#include <unordered_map>
#include <map>
#include <cstdint>
#include "util.h"

class CompatibleType{
    public:
        CompatibleType();
        CompatibleType(std::string);
        CompatibleType(const CompatibleType& compatible_type);
        std::string name() const;
        bool operator==(const CompatibleType& second_type) const;
        bool operator>(const CompatibleType& second_type) const;
        bool operator<(const CompatibleType& second_type) const;
    private:
        std::string type;
};
struct CompatibleTile{
    uint16_t tile_id;
    CompatibleType top;
    CompatibleType left;
    CompatibleType right;
    CompatibleType bottom;
};
class CompatibleChecker{
    public:
        CompatibleChecker(int tile_count, std::set<CompatibleType> compatible_types);
        void putCompatible(CompatibleTile compatible_tile);
        CompatibleType compatibleType(uint16_t tile, d2kmapapi::Direction direction);
        bool areCompatible(uint16_t tile1, d2kmapapi::Direction tile1_direction, uint16_t tile2);
    private:
        std::set<CompatibleType> compatible_types;
        std::unordered_map<uint16_t, std::array<CompatibleType, 4>> compatibility;
};
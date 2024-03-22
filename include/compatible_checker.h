#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <cstdint>

class CompatibleType{
    public:
        CompatibleType(std::string);
        bool operator==(const CompatibleType& second_type) const;
    private:
        std::string type;
};
enum Direction{
    top, left, right, bottom
};
class CompatibleCheker{
    public:
        CompatibleCheker(int tile_count, std::vector<CompatibleType> compatible_types);
        void putCompatible(uint16_t tile, CompatibleType top, CompatibleType left, CompatibleType right, CompatibleType bottom);
        std::string compatible(uint16_t, Direction direction);
    private:
        std::vector<CompatibleType> compatible_types;
        std::unordered_map<uint16_t, std::array<short, 4>> compatibility;
};
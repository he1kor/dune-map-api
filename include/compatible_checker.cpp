#include "compatible_checker.h"
#include <stdexcept>

CompatibleType::CompatibleType(std::string type) : type(type){}

bool CompatibleType::operator==(const CompatibleType &second_type) const{
    return type == second_type.type;
};

CompatibleCheker::CompatibleCheker(int tile_count, std::set<CompatibleType> compatible_types) : compatible_types(compatible_types){
    compatibility.reserve(tile_count);
}

void CompatibleCheker::putCompatible(uint16_t tile, CompatibleType top, CompatibleType left, CompatibleType right, CompatibleType bottom){
    auto i_top = compatible_types.find(top);
    auto i_left = compatible_types.find(left);
    auto i_right = compatible_types.find(right);
    auto i_bottom = compatible_types.find(bottom);
    auto end = compatible_types.end();
    if (i_top == end || i_left == end || i_right == end || i_bottom == end)
        throw std::invalid_argument("Unknown compatible type!");
    
    compatibility[tile] = std::array{&(*i_top), &(*i_left), &(*i_right), &(*i_bottom)};
}

CompatibleType CompatibleCheker::compatibleType(uint16_t tile, Direction direction){
    return *(compatibility.at(tile)[direction]);
}

bool CompatibleCheker::areCompatible(uint16_t tile1, Direction tile1_direction, uint16_t tile2){
    return compatibleType(tile1, tile1_direction) == compatibleType(tile2, Direction(3-int(tile1_direction)));
}

#include "compatible_checker.h"
#include <stdexcept>

CompatibleType::CompatibleType() : type(""){}
CompatibleType::CompatibleType(std::string type) : type(type){}

CompatibleType::CompatibleType(const CompatibleType &compatible_type){
    type = compatible_type.type;
}

std::string CompatibleType::name() const{
    return type;
}

bool CompatibleType::operator==(const CompatibleType &second_type) const{
    return type == second_type.type;    
}
bool CompatibleType::operator>(const CompatibleType &second_type) const{
    return type > second_type.type;
};
bool CompatibleType::operator<(const CompatibleType &second_type) const{
    return type < second_type.type;
};

CompatibleChecker::CompatibleChecker(int tile_count, std::set<CompatibleType> compatible_types) : compatible_types(compatible_types){
    compatibility.reserve(tile_count);
}

void CompatibleChecker::putCompatible(CompatibleTile cmptbl_tl){
    auto i_top = compatible_types.find(cmptbl_tl.top);
    auto i_left = compatible_types.find(cmptbl_tl.left);
    auto i_right = compatible_types.find(cmptbl_tl.right);
    auto i_bottom = compatible_types.find(cmptbl_tl.bottom);
    auto end = compatible_types.end();
    if (i_top == end || i_left == end || i_right == end || i_bottom == end)
        throw std::invalid_argument("Unknown compatible type!");
    compatibility[cmptbl_tl.tile_id] = std::array{cmptbl_tl.top, cmptbl_tl.left, cmptbl_tl.right, cmptbl_tl.bottom};
}
CompatibleType CompatibleChecker::compatibleType(uint16_t tile, d2kmapapi::Direction direction) const{
    return compatibility.at(tile)[direction];
}

std::vector<CompatibleType> CompatibleChecker::compatibleTypes(DirectionalLine directional_line) const{
    std::vector<CompatibleType> compatible_types;
    for (uint16_t tile : directional_line.getTiles()){
        compatible_types.push_back(compatibleType(tile, directional_line.getNormalDirection()));
    }
    return compatible_types;
}

bool CompatibleChecker::areCompatible(uint16_t tile1, d2kmapapi::Direction tile1_direction, uint16_t tile2) const {
    return compatibility.at(tile1)[tile1_direction] == compatibility.at(tile2)[reverse(tile1_direction)];
}

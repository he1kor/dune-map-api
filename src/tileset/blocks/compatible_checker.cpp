#include "compatible_checker.h"
#include <stdexcept>

CompatibleType::CompatibleType() : type_name(""){}
CompatibleType::CompatibleType(const char* str) : type_name(str){}
CompatibleType::CompatibleType(std::string type_name) : type_name(type_name) {}

CompatibleType::CompatibleType(const CompatibleType &compatible_type){
    type_name = compatible_type.type_name;
}

const CompatibleType CompatibleType::null = CompatibleType("");

std::string CompatibleType::name() const{
    return type_name;
}

bool CompatibleType::operator==(const CompatibleType &second_type) const{
    return type_name == second_type.type_name;    
}
bool CompatibleType::operator>(const CompatibleType &second_type) const{
    return type_name > second_type.type_name;
};
bool CompatibleType::operator<(const CompatibleType &second_type) const{
    return type_name < second_type.type_name;
};


CompatibleTile::CompatibleTile(uint16_t tile_id, CompatibleType all_side_compatible_type)
    : tile_id{tile_id},
    top{all_side_compatible_type},
    left{all_side_compatible_type},
    right{all_side_compatible_type},
    bottom{all_side_compatible_type}{}

CompatibleTile::CompatibleTile(uint16_t tile_id, CompatibleType top, CompatibleType left, CompatibleType right, CompatibleType bottom)
    : tile_id{tile_id},
    top{top},
    left{left},
    right{right},
    bottom{bottom}{}



CompatibleChecker::CompatibleChecker(int tile_count){
    compatibility.reserve(tile_count);
}

void CompatibleChecker::putCompatible(CompatibleTile cmptbl_tl)
{
    compatibility[cmptbl_tl.tile_id] = std::array{cmptbl_tl.top, cmptbl_tl.left, cmptbl_tl.right, cmptbl_tl.bottom};
}
CompatibleType CompatibleChecker::compatibleType(uint16_t tile, d2kmapapi::Direction direction) const{
    if (!compatibility.count(tile))
        throw std::invalid_argument("Tile " + std::to_string(tile) + " has no compatible types!");
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
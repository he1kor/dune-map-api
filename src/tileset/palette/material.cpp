#include "material.h"
#include <algorithm>

Material::Material(){}

Material::Material(uint16_t tile) : tiles{tile}{}

Material::Material(int x, int y, int width, int height){
    for (int r = y; r < y + height; r++){
        for (int c = x; c < x + width; c++){
            tiles.push_back(r * 20 + c);
        }
    }
}
bool Material::containsTile(uint16_t unknown_tile) const{
    for (auto &existing_tile : tiles)
    {
        if (existing_tile == unknown_tile)
            return true;
    }
    return false;
}

const uint16_t &Material::operator[](int i)
{
    return tiles.at(i);
}

void Material::addTile(uint16_t tile){
    tiles.push_back(tile);
}

bool Material::operator==(const Material &other) const{
    if (tiles.size() != other.tiles.size())
        return false;

    std::vector<uint16_t> sortedThis = tiles;
    std::vector<uint16_t> sortedOther = other.tiles;

    std::sort(sortedThis.begin(), sortedThis.end());
    std::sort(sortedOther.begin(), sortedOther.end());

    return sortedThis == sortedOther;
}

int Material::size() const{
    return tiles.size();
}
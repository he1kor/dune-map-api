#include "material.h"
#include "global.h"
#include <algorithm>

Material::Material(){}

Material::Material(uint16_t tile) : indexed_tiles{tile}, set_tiles{tile}{}

Material::Material(int x, int y, int width, int height){
    for (int r = y; r < y + height; r++){
        for (int c = x; c < x + width; c++){
            indexed_tiles.push_back(r * d2kmapapi::tileset_width + c);
            set_tiles.insert(r * d2kmapapi::tileset_width + c);
        }
    }
}

bool Material::containsTile(uint16_t unknown_tile) const{
    return set_tiles.find(unknown_tile) != set_tiles.end();
}

const uint16_t &Material::operator[](int i) const{
    return indexed_tiles.at(i);
}

void Material::addTile(uint16_t tile){
    indexed_tiles.push_back(tile);
    set_tiles.insert(tile);
}

bool Material::operator==(const Material &other) const{
    if (indexed_tiles.size() != other.indexed_tiles.size())
        return false;

    std::vector<uint16_t> sortedThis = indexed_tiles;
    std::vector<uint16_t> sortedOther = other.indexed_tiles;

    std::sort(sortedThis.begin(), sortedThis.end());
    std::sort(sortedOther.begin(), sortedOther.end());

    return sortedThis == sortedOther;
}

int Material::size() const{
    return indexed_tiles.size();
}
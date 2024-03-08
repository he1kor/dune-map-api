#include "material.h"
#include <algorithm>

Material::Material(){}

Material::Material(int x, int y, int width, int height){
    for (int r = y; r < y + height; r++){
        for (int c = x; c < x + width; c++){
            tiles.push_back(r * 20 + c);
        }
    }
}
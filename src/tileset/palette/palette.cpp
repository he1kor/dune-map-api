#include "palette.h"
#include <random>
#include <time.h>

Palette::Palette(){
    srand(time(0));
}

Palette::Palette(std::map<std::string, Material>& materials) : materials(materials){
    srand(time(0));
}

Palette::Palette(Palette&& palette) : materials{std::move(palette.materials)}{}

Palette::Palette(Palette &palette) : materials{palette.materials}{

}

Palette &Palette::operator=(Palette &&palette){
    if (this != &palette){
        materials = std::move(palette.materials);
    }
    return *this;
}

void Palette::addMaterial(std::string material_name, const Material& material){
    materials[material_name] = material;
}

const Material& Palette::operator[](std::string material_name){
    return materials.at(material_name);
}

void Palette::removeMaterial(std::string material_name){
    materials.erase(materials.find(material_name));
}

uint16_t Palette::pick(std::string material_name){
    Material& material = materials.at(material_name);
    int ranged_rand = std::rand() % material.size();
    return material[ranged_rand];
}
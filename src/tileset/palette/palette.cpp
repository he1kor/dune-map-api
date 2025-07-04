#include "palette.h"
#include "util.h"
#include <random>
#include <time.h>
#include <stdexcept>


Palette::Palette(){}

Palette::Palette(const std::map<std::string, Material>& materials) : materials(materials){
    srand(time(0));
}

Palette::Palette(Palette&& palette) : materials{std::move(palette.materials)}{}

Palette::Palette(const Palette &palette) : materials{palette.materials}{

}

Palette &Palette::operator=(Palette &&palette){
    if (this != &palette){
        materials = std::move(palette.materials);
    }
    return *this;
}

void Palette::addMaterial(const std::string& material_name, const Material& material){
    materials[material_name] = material;
}

const Material& Palette::operator[](const std::string& material_name){
    return materials.at(material_name);
}

Material Palette::findMaterial(uint16_t id){
    for (auto &material_pair : materials)
    {
        if (material_pair.second.containsTile(id))
            return material_pair.second;
    }
    return Material(id);
}
std::string Palette::findMaterialName(uint16_t id){
    for (auto &material_pair : materials)
    {
        if (material_pair.second.containsTile(id))
            return material_pair.first;
    }
    return "";
}

void Palette::removeMaterial(const std::string& material_name){
    materials.erase(materials.find(material_name));
}
uint16_t Palette::pick(const Material& material){
    int ranged_rand = d2kmapapi::getRandomNumber(0, material.size()-1);
    return material[ranged_rand];
}
uint16_t Palette::pick(const std::string& material_name){
    return pick((*this)[material_name]);
}
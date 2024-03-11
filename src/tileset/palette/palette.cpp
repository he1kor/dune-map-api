#include "palette.h"
#include <random>
#include <time.h>

Palette::Palette(){
    srand(time(0));
}

Palette::Palette(std::map<const char*, Material>& materials) : materials(materials){
    srand(time(0));
}

void Palette::addMaterial(const char* material_name, const Material& material){
    materials[material_name] = material;
}

const Material& Palette::operator[](const char* material_name){
    return materials.at(material_name);
}

void Palette::removeMaterial(const char* material_name){
    materials.erase(materials.find(material_name));
}

uint16_t Palette::pick(const char* material_name){
    Material& material = materials.at(material_name);
    int ranged_rand = std::rand() % material.size();
    return material[ranged_rand];
}
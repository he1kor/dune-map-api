#pragma once
#include "material.h"
#include <map>
#include <cstdint>
#include <string>

class Palette{
    public:
        Palette(std::map<std::string, Material>& materials);
        Palette();
        Palette(Palette&& palette);
        Palette& operator=(Palette&& palette);
        uint16_t pick(std::string material_name);
        const Material& operator[](std::string material_name);
        void addMaterial(std::string material_name, const Material& material);
        void removeMaterial(std::string material_name);
    private:
        std::map<std::string, Material> materials;
};
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
        Palette(Palette& palette);
        Palette& operator=(Palette&& palette);
        static uint16_t pick(Material material);
        uint16_t pick(std::string material_name);
        const Material& operator[](std::string material_name);
        Material findMaterial(uint16_t id);
        void addMaterial(std::string material_name, const Material& material);
        void removeMaterial(std::string material_name);
    private:
        std::map<std::string, Material> materials;
};
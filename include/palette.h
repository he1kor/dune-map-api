#pragma once
#include "material.h"
#include <map>
#include <cstdint>

class Palette{
    public:
        Palette(std::map<const char*,Material> materials);
        Palette();
        ~Palette();
        uint16_t pick(const char* material_name);
        const Material& operator[](const char* material_name);
        void addMaterial(const char* material_name, const Material& material);
        void removeMaterial(const char*);
    private:
        std::map<const char*,Material> materials;
};
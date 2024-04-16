#pragma once
#include "material.h"
#include <map>
#include <cstdint>
#include <string>
/*!
	\brief Class-wrapper for all materials. Materials are mapped by their names. Materials are used for random picking tile ID.
*/
class Palette{
    public:
        /**
         * \brief Constructor with initial material map.
         * \param materials Map string to Material for copying it to material field.
        */
        Palette(const std::map<std::string, Material>& materials);
        Palette();
        Palette(Palette&& palette);
        Palette(const Palette& palette);
        Palette& operator=(Palette&& palette);
        static uint16_t pick(const Material& material);
        uint16_t pick(const std::string& material_name);
        const Material& operator[](const std::string& material_name);
        Material findMaterial(uint16_t id);
        void addMaterial(const std::string& material_name, const Material& material);
        void removeMaterial(const std::string& material_name);
    private:
        std::map<std::string, Material> materials;
};
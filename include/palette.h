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

        /**
         * \brief Default constructor. Field Map materials is empty.
        */
        Palette();

        /**
         * \brief Move constructor.
        */
        Palette(Palette&& palette);
        
        /**
         * \brief Copy constructor.
        */
        Palette(const Palette& palette);
        
        /**
         * \brief Move assignment operator.
        */
        Palette& operator=(Palette&& palette);

        /**
         * \brief Picks a random tile ID from the provided material and returns it.
         * \param material - Material to pick tile ID.
         * \return Random tile ID of the provided material.
        */
        static uint16_t pick(const Material& material);

        /**
         * \brief Picks a random tile ID from the materials[material_name] and returns it.
         * \param material_name Name of the material to assign from materials map.
         * \return Random tile ID of the received material.
        */
        uint16_t pick(const std::string& material_name);

        /**
         * \brief Reference to const material getter by its name in the materials Map.
         * \param material_name Name of the material to assign from materials map.
         * \return Received material by its name.
        */
        const Material& operator[](const std::string& material_name);
        
        /**
         * \brief Takes a tile ID and returns material that uses this tile ID. If materials doesn't contain any material that uses provided ID, it returns single-tile material with provided tile ID.
         * \param id Tile ID that should be in the found Material.
         * \return Found Material or a new single-tile Material that contains provided id.
        */
        Material findMaterial(uint16_t id);

        std::string findMaterialName(uint16_t id);

        /**
         * \brief Adds a new key-value pair to materials.
         * \param material_name Name which will be mapped to Material.
         * \param material New material in materials mapped with material_name.
        */
        void addMaterial(const std::string& material_name, const Material& material);
        
        /**
         * \brief Removes existing key-value pair from materials. If provided material_name doesn't exist in materials, it throws an exception.
         * \param material_name Key of the materials key-value pair which will be removed.
        */
        void removeMaterial(const std::string& material_name);
    private:
        std::map<std::string, Material> materials;
};
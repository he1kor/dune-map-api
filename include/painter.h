#pragma once
#include <string>
#include "palette.h"
#include "smart_map.h"

/*!
	\brief Class containing Map pointer, Palette pointer and methods for ease of use. Used for smart change of map tiles. 
*/
class Painter{
    public:
        /**
         * \brief Default constructor with late Map and Palette initialization.
        */
        Painter();
        /**
         * \brief Constructor with late Palette initialization.
         * \param map Pointer to the map that should be painted.
        */
        Painter(SmartMap* map);
        /**
         * \brief Constructor with no late initialization fields.
         * \param map Pointer to the map that should be painted.
         * \param palette Pointer to the palette which materials should be used.
        */
        Painter(SmartMap* map, Palette* palette);

        /**
         * \brief Determines whether tile at provided coords consists of provided material.
         * \param x X coord of the tile to check.
         * \param y Y coord of the tile to check.
         * \param material Material to compare with tile's one.
        */
        bool isMaterial(int x, int y, const Material& material);
        
        /**
         * \brief Determines whether tile at provided coords consists of provided material name.
         * \param x X coord of the tile to check.
         * \param y Y coord of the tile to check.
         * \param material String name of the material to compare with tile's one. If the material is not in this palette, it throws an exception.
        */
        bool isMaterial(int x, int y, const std::string& material_name);

        /**
         * \brief Map pointer setter. Changes what map to paint.
         * \param map The new map to paint.
        */
        void setMap(SmartMap* map);

        /**
         * \brief Palette pointer setter. Changes from what palette pick materials.
         * \param palette The new palette to use.
        */
        void setPalette(Palette* palette);

        /**
         * \brief Sets at provided coords a random tile of provided material.
         * \param x X coord of the tile to paint.
         * \param y Y coord of the tile to paint.
         * \param material Material to use for picking random tile.
        */
        void paint(int x, int y, const Material& material);

        /**
         * \brief Sets at provided coords a random tile of material that provided by its name.
         * \param x X coord of the tile to paint.
         * \param y Y coord of the tile to paint.
         * \param material Name of the material to use for picking random tile. If the material is not in this palette, it throws an exception.
        */
        void paint(int x, int y, const std::string& material_name);


        void holdPaint(int x, int y, const Material& material);
        void holdPaint(int x, int y, const std::string& material_name);
        /**
         * \brief Flood fill of the provided replaced_material, started at provided coords, replaced with provided fill_material.
         * \param x X coord of the tile to start filling.
         * \param y Y coord of the tile to start filling.
         * \param fill_material Material that will be used for filling (for each coord it will pick a random tile ID).
         * \param replaced_material Material that will be replaced with the new (any tile ID of the replaced_material will be replaced with the new one).
        */
        void fill(int x, int y, const Material& fill_material, const Material& replaced_material);

        /**
         * \brief Flood fill of the provided replaced_material name, started at provided coords, replaced with provided fill_material name.
         * \param x X coord of the tile to start filling.
         * \param y Y coord of the tile to start filling.
         * \param fill_material Material name that will be used for filling (for each coord it will pick a random tile ID). If the material is not in this palette, it throws an exception.
         * \param replaced_material Material name that will be replaced with the new (any tile ID of the replaced_material will be replaced with the new one). If the material is not in this palette, it throws an exception.
        */
        void fill(int x, int y, const std::string& fill_material_name, const std::string& replaced_material_name);

        /**
         * \brief Flood fill of the tile placed in map[y][x] if use_palette is False, or of the material placed in map[y][x] if use_material is True, started at provided coords, replaced with provided fill_material.
         * \param x X coord of the tile to start filling.
         * \param y Y coord of the tile to start filling.
         * \param fill_material Material that will be used for filling (for each coord it will pick a random tile ID).
         * \param use_palette If set to True, the tile ID at map[y][x] will be picked as material and that material will be the replaced_material. Else, the tile ID on that coords will be the only replaced tile ID.
        */
        void fill(int x, int y, const Material& fill_material, bool use_palette);

        /**
         * \brief Flood fill of the tile placed in map[y][x] if use_palette is False, or of the material placed in map[y][x] if use_material is True, started at provided coords, replaced with provided fill_material.
         * \param x X coord of the tile to start filling.
         * \param y Y coord of the tile to start filling.
         * \param fill_material Material name that will be used for filling (for each coord it will pick a random tile ID). If the material is not in this palette, it throws an exception.
         * \param use_palette If set to True, the tile ID at map[y][x] will be picked as material and that material will be the replaced_material. Else, the tile ID on that coords will be the only replaced tile ID.
        */
        void fill(int x, int y, const std::string& fill_material_name, bool use_palette);
    private:
        bool isOutOfBounds(int x, int y);
        bool checkMapSet();
        bool checkPaletteSet();
        SmartMap* map = nullptr;
        Palette* palette = nullptr;
};
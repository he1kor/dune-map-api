#pragma once
#include <string>
#include "map.h"
#include "palette.h"

/*!
	\brief Class containing Map pointer, Palette pointer and methods for ease of use. Used for smart change of map tiles. 
*/
class Painter{
    public:
        Painter();
        Painter(Map* map);
        Painter(Map* map, Palette* palette);
        bool isMaterial(int x, int y, const Material& material);
        bool isMaterial(int x, int y, const std::string& material_name);
        void setMap(Map* map);
        void setPalette(Palette* palette);
        void paint(int x, int y, const Material& material);
        void paint(int x, int y, const std::string& material_name);

        void fill(int x, int y, const Material& fill_material, const Material& replaced_material);
        void fill(int x, int y, const std::string& fill_material_name, const std::string& replaced_material_name);
        void fill(int x, int y, const Material& fill_material, bool use_palette);
        void fill(int x, int y, const std::string& fill_material_name, bool use_palette);
    private:
        bool isOutOfBounds(int x, int y);
        bool checkMapSet();
        bool checkPaletteSet();
        Map* map;
        Palette* palette;
};
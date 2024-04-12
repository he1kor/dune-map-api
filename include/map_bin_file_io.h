#pragma once
#include "map.h"
#include "file_reader.h"
#include <fstream>

/*!
	\brief Class for saving and loading map binaries.
*/
class MapBinFileIO : public FileReader {
    public:        
        MapBinFileIO();
        MapBinFileIO(Map& map, const char file_path[]);
        void create(Map& map, const char file_path[]);
        void save(Map& map);
        Map load();
        void saveTile(Tile& tile, uint16_t x, uint16_t y);
        Tile loadTile(uint16_t x, uint16_t y);
    private:
        uint16_t width;
        uint16_t height;
};
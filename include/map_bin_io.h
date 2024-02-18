#pragma once
#include "map.h"
#include <fstream>

class MapBinIO{
    public:        
        MapBinIO();
        MapBinIO(Map& map, const char file_path[]);
        bool fileOpened();
        void open(const char file_path[]);
        bool close();
        void create(Map& map, const char file_path[]);
        void save(Map& map);
        Map load();
        void saveTile(Tile& tile, uint16_t x, uint16_t y);
        Tile loadTile(uint16_t x, uint16_t y);
        static const char FILE_EXTENSION[];
    private:
        bool checkOpenedError();
        bool checkNotOpenedError();
        bool checkFileIssues();
        bool checkFileExtensionError(const char file_path[]);
        bool checkFileExistError(const char file_path[]);
        bool checkFileNotExistError(const char file_path[]);
        std::fstream bin_file;
        uint16_t width;
        uint16_t height;
};
#pragma once
#include <fstream>
#include "tileset_properties.h"

class TilesetJsonI{
    public:
        TilesetJsonI();
        TilesetJsonI(const char file_path[]);
        void open(const char file_path[]);
        bool close();
        tilesetProperties load();
        
        static const char FILE_EXTENSION[];
    private:
        std::fstream json_file;
};
#pragma once
#include "palette.h"

class TilesetJsonI{
    public:
        TilesetJsonI();
        void open(const char file_path[]);
        bool close();
        Palette load();
};
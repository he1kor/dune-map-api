#include "library.h"
#include "map.h"
#include "map_bin_io.h"
#include <iostream>

void printMap(Map& map){
    std::cout << "\n";
    for (int r = 0; r < map.height(); r++){
        for (int c = 0; c < map.width(); c++){
            std::cout << map[r][c].tileID << " " << map[r][c].entityID << "\t";
        }
        std::cout <<  "\n";
    }
}

int main() {
    MapBinIO map_bin_io;
    Map map(128, 128);
    map_bin_io.create(map, "temp.map");
    map_bin_io.open("temp.map");
    
    for (int y = 0; y < map.height(); y++){
        for (int x = 0; x < 20; x++){
            map[y][x].tileID = 20*y + x;
        }
    }

    map_bin_io.save(map);
    map_bin_io.close();
    return 0;
}
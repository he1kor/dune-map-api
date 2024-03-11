#include "library.h"
#include "map.h"
#include "map_bin_io.h"
#include "palette.h"
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

    Palette palette;
    palette.addMaterial("rock", Material(0, 0, 5, 6));
    palette.addMaterial("sand", Material(5, 0, 2, 2));

    std::cout << "test: \n";
    for (int i = 0; i < 100; i++){
        std::cout << palette.pick("rock") << "\t";
    }
    
    std::cout << "\nTEST\n";

    for (int i = 0; i < 100; i++){
        std::cout << palette.pick("sand") << "\t";
    }
    return 0;
}
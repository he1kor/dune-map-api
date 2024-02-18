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
    // int height = 10;
    // int width = 16;
    // Map map = Map(width, height);
    // for (int r = 0; r < height; r++){
    //     for (int c = 0; c < width; c++){
    //         map[r][c].entityID = 10 + (r * c);
    //         map[r][c].tileID = r * c;
    //     }
    // }

    // printMap(map);
    // MapBinIO map_bin_io;
    // map_bin_io.create(map, "test.map");
    // map_bin_io.open("test.map");
    // Map map2 = map_bin_io.load();
    // printMap(map2);

    MapBinIO map_bin_io;
    map_bin_io.open("temp.map");
    Map map = map_bin_io.load();
    int r = 30;
    int a = (int) map.height() / 2;
    int b = (int) map.width() / 2;

    for (int y = 0; y < map.height(); y++){
        for (int x = 0; x < map.width(); x++){
            map[x][y].tileID = 0;
            map[x][y].entityID = 0;
            if (((x-a)*(x-a)) + ((y-b)*(y-b)) < r*r){
                map[x][y].tileID = 554;
            }
        }
    }
    map_bin_io.save(map);
     return 0;
}
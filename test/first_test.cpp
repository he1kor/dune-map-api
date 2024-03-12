#include "map.h"
#include "map_bin_file_io.h"
#include "palette.h"
#include <tileset_json_i.h>
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
    MapBinFileIO map_bin_file;
    Map map(128, 128);
    TilesetProperties tilesetProperties = load("data/tileset.json");
    map_bin_file.create(map, "temp.map");
    map_bin_file.open("temp.map");
    
    for (int y = 0; y < map.height(); y++){
        for (int x = 0; x < map.width(); x++){
            map[y][x].tileID = tilesetProperties.palette.pick("dunes");
        }
    }

    map_bin_file.save(map);
    map_bin_file.close();


    return 0;
}
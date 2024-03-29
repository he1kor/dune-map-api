#include "map.h"
#include "map_bin_file_io.h"
#include "palette.h"
#include "painter.h"
#include "edge.h"
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
    TilesetProperties tilesetProperties = load("data/tileset.json");
    MapBinFileIO map_bin_file;
    map_bin_file.open("temp.map");
    Map map = map_bin_file.load();
    Painter painter(&map, &tilesetProperties.palette);
    uint16_t tile = tilesetProperties.palette.pick("rock");
    tilesetProperties.compatible_checker.areCompatible(tile, Direction::RIGHT, tile);
    Vertical vert = Vertical::fromLeft(0, 0);
    painter.fill(40, 23, "sand", true);
    painter.fill(0, 0, "rock", true);
    painter.fill(40, 0, "rock", true);
    map_bin_file.save(map);
    map_bin_file.close();


    return 0;
}
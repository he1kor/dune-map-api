#include "map.h"
#include "map_bin_file_io.h"
#include "palette.h"
#include "painter.h"
#include "edge.h"
#include "util.h"
#include <tileset_json_i.h>
#include <iostream>
#include <chrono>

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
    TilesetProperties tileset_properties = load("data/tileset.json");
    MapBinFileIO map_bin_file;
    map_bin_file.open("test.map");
    Map map = map_bin_file.load();
    BlockPlacer block_placer(&tileset_properties.block_set);
    block_placer.setMap(&map);


    Horizontal horizontal = Horizontal::fromBottom(5,6,5);
    auto coords = horizontal.onTop();
    std::vector<uint16_t> tiles;
    for (auto [x, y] : coords){
        tiles.push_back(map[y][x].tileID);
    }
    DirectionalLine line(tiles, d2kmapapi::Direction::DOWN);
    std::vector<Block> blocks = tileset_properties.block_set.compatibleBlocks(line, "rock_cliffs");
    std::cout << blocks.size() << "\n\n";
    block_placer.placeEdge(horizontal, d2kmapapi::Direction::DOWN, blocks[3]);
    for (auto block : blocks){
        std::cout << block_placer.getShift(horizontal, d2kmapapi::Direction::DOWN, block) << "\n";
    }
    map_bin_file.save(map);
    std::cout << "done!";
    return 0;
}

//TilesetProperties tilesetProperties = load("data/tileset.json");
    //MapBinFileIO map_bin_file;
    //map_bin_file.open("temp.map");
    //Map map = map_bin_file.load();
    //Painter painter(&map, &tilesetProperties.palette);
    //painter.fill(40, 23, "sand", true);
    //painter.fill(0, 0, "rock", true);
    //painter.fill(40, 0, "rock", true);
    //uint16_t tile = tilesetProperties.palette.pick("rock");
    //tilesetProperties.compatible_checker.areCompatible(tile, d2kmapapi::Direction::RIGHT, tile);
    //Vertical vert = Vertical::fromLeft(0, 0);
    //auto groups = tilesetProperties.block_set.getGroups();
    //for (auto group : groups){
    //    std::cout << group << ":\n";
    //    for (Block block : tilesetProperties.block_set[group]){
    //        auto m = block.getMatrix();
    //        for (auto v : m){
    //            for (uint16_t t : v){
    //                std::cout << t << "\t";
    //            }
    //            std::cout << "\n";
    //        }
    //        std::cout << "\n";
    //    }
    //    std::cout << "\n------------------------\n";
    //}
    //std::cout << "\n<<------------------------>>\n";
    //auto block = tilesetProperties.block_set["rock_cliffs"][1];
    //auto m = block.getMatrix();
    //auto t = block.getRightTiles();
    //for (auto t1 : t){
    //    std::cout << t1 << "\t";
    //}
    //std::cout << "\n\n";
    //for (auto v : m){
    //    for (uint16_t t : v){
    //        std::cout << t << "\t";
    //    }
    //    std::cout << "\n";
    //}
    //std::cout << "\n\n";
    //auto start = std::chrono::high_resolution_clock::now();
    //auto blocks = tilesetProperties.block_set.compatibleBlocks(DirectionalLine(tilesetProperties.block_set["rock_cliffs"][1].getRightTiles(), d2kmapapi::Direction::RIGHT), "rock_cliffs");
    //auto stop = std::chrono::high_resolution_clock::now();
    //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    //
    //for (auto block : blocks){
    //    auto m = block.getMatrix();
    //        for (auto v : m){
    //            for (uint16_t t : v){
    //                std::cout << t << "\t";
    //            }
    //            std::cout << "\n";
    //        }
    //        std::cout << "\n";
    //}
    //map_bin_file.save(map);
    //map_bin_file.close();
    //std::cout << "passed in " << duration.count() << " microsecs";
    //return 0;
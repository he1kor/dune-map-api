#include "map.h"
#include "map_bin_file_io.h"
#include "palette.h"
#include "painter.h"
#include "edge.h"
#include "util.h"
#include "tileset_json_i.h"
#include "smart_map.h"
#include "directed_edge.h"
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

int main(){
    TilesetProperties tileset_properties = load("data/tileset.json");
    MapBinFileIO map_bin_file;
    map_bin_file.open("test.map");
    auto map = SmartMap::fromMap(map_bin_file.load());
    BlockPlacer block_placer(&tileset_properties.block_set);
    block_placer.setMap(&map);
    map.initHistoryStack();
    Painter painter(&map, &tileset_properties.palette);

    /*TODO: fix not placed:

                "x": 16,
                "y": 33,
                "width": 1,
                "height": 2,
                "compatibility_up": ["rock_plain"],
                "compatibility_left": ["forward_rock_cliff", "forward_rock_cliff"],
                "compatibility_right": ["forward_rock_cliff", "forward_rock_cliff"],
                "compatibility_bottom": ["sand"]
    */

    Edge edge = Horizontal::fromTop(63, 64, 46);
    DirectedEdge directed_edge(edge, d2kmapapi::Direction::DOWN);

    //for (int i = 0; i < blocks.size(); i++){
    //    std::cout << i << "\n";
    //    Edge edge = Vertical::fromLeft(18 + i * 4, 19 + i * 4, 6);
    //    block_placer.smartEdgePlace(edge, d2kmapapi::Direction::RIGHT, blocks[i]);
    //}
    for (int i = 0; i < 120; i++){
        std::cout << i << "\t";
        auto blocks = block_placer.compatibleBlocks(directed_edge.getEdge(), directed_edge.getDirection(), "rock_cliffs");
        std::cout << blocks.size() << "\nDirection: ";
        std::cout << directed_edge.getDirection() << "\tX: " << directed_edge.getEdge().getX() << "\tY: " << directed_edge.getEdge().getY() << "\tSize: " << "\t" << directed_edge.getEdge().getSize() << '\n';
        directed_edge = block_placer.smartPlaceNextOnEdge(directed_edge.getEdge(), directed_edge.getDirection(), blocks[d2kmapapi::getRandomNumber(0, blocks.size()-1)], {"backward_rock_cliff", "forward_rock_cliff"});

        map_bin_file.save(map);
    }
    map_bin_file.save(map);
    std::cout << "done!";
    return 0;
}
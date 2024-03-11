#include "map_bin_file.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>

using namespace std;

MapBinFile::MapBinFile(){
    FILE_EXTENSION = ".map";
}

MapBinFile::MapBinFile(Map& map, const char file_path[]){
    FILE_EXTENSION = ".map";
    create(map, file_path);
}

void MapBinFile::create(Map& map, const char file_path[]){
    checkFileExtensionError(file_path);
    file.open(file_path, ios::binary | ios::out | ios::trunc);
    checkFileIssues();
    save(map);
    file.close();
}

void MapBinFile::save(Map& map){
    checkNotOpenedError();
    width = map.width();
    height = map.height();
    file.seekp(0, ios::beg);
    file.write((char*) &width, sizeof(uint16_t));
    file.write((char*) &height, sizeof(uint16_t));
    for (int r = 0; r < map.height(); r++){
        for (int c = 0; c < map.width(); c++){
            file.write((char *) &map[r][c], sizeof(Tile));
        }
    }
}

Map MapBinFile::load(){
    checkNotOpenedError();
    checkFileIssues();
    file.read((char*) &width, sizeof(uint16_t));
    file.read((char*) &height, sizeof(uint16_t)); 
    Map map(width, height);
    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            file.read((char*) &map[r][c], sizeof(Tile));
        }
    }
    return map;
}

void MapBinFile::saveTile(Tile& tile, uint16_t x, uint16_t y){
    file.seekp(
        (sizeof(uint16_t) * 2)
        + (width * y)
        + x,
          ios::beg);
    file.write((char*) &tile, sizeof(Tile));
}

Tile MapBinFile::loadTile(uint16_t x, uint16_t y){
    Tile tile;
    file.seekp(
        (sizeof(uint16_t) * 2)
        + (width * y)
        + x,
          ios::beg);
    file.read((char*) &tile, sizeof(Tile));
    return tile;
}
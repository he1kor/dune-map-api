#include "map_bin_file_io.h"
#include "file_checks.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>

MapBinFileIO::MapBinFileIO(){
    FILE_EXTENSION = ".map";
}

MapBinFileIO::MapBinFileIO(Map& map, const char file_path[]){
    FILE_EXTENSION = ".map";
    create(map, file_path);
}

void MapBinFileIO::create(Map& map, const char file_path[]){
    checkFileExtensionError(file_path, FILE_EXTENSION);
    file.open(file_path, std::ios::binary | std::ios::out | std::ios::trunc);
    checkFileIssues(file);
    save(map);
    file.close();
}

void MapBinFileIO::save(Map& map){
    checkNotOpenedError(file);
    width = map.width();
    height = map.height();
    file.seekp(0, std::ios::beg);
    file.write((char*) &width, sizeof(uint16_t));
    file.write((char*) &height, sizeof(uint16_t));
    for (int r = 0; r < map.height(); r++){
        for (int c = 0; c < map.width(); c++){
            file.write((char *) &map[r][c], sizeof(Tile));
        }
    }
}

Map MapBinFileIO::load(){
    checkNotOpenedError(file);
    checkFileIssues(file);
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

void MapBinFileIO::saveTile(Tile& tile, uint16_t x, uint16_t y){
    file.seekp(
        (sizeof(uint16_t) * 2)
        + (width * y)
        + x,
          std::ios::beg);
    file.write((char*) &tile, sizeof(Tile));
}

Tile MapBinFileIO::loadTile(uint16_t x, uint16_t y){
    Tile tile;
    file.seekp(
        (sizeof(uint16_t) * 2)
        + (width * y)
        + x,
          std::ios::beg);
    file.read((char*) &tile, sizeof(Tile));
    return tile;
}
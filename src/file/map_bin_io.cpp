#include "map_bin_io.h"
#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>

using namespace std;

const char MapBinIO::FILE_EXTENSION [] = ".map";

MapBinIO::MapBinIO(){}

MapBinIO::MapBinIO(Map& map, const char file_path[]){
    create(map, file_path);
}

bool MapBinIO::fileOpened(){
    return bin_file.is_open();
}

void MapBinIO::open(const char file_path[]){
    checkFileExtensionError(file_path);
    checkFileNotExistError(file_path);
    bin_file.open(file_path, ios::binary | ios::out | ios::in);
    checkFileIssues();
}

bool MapBinIO::close(){
    checkNotOpenedError();
    bin_file.close();
}

void MapBinIO::create(Map& map, const char file_path[]){
    checkFileExtensionError(file_path);
    bin_file.open(file_path, ios::binary | ios::out | ios::trunc);
    checkFileIssues();
    save(map);
    bin_file.close();
}

void MapBinIO::save(Map& map){
    checkNotOpenedError();
    width = map.width();
    height = map.height();
    bin_file.seekp(0, ios::beg);
    bin_file.write((char*) &width, sizeof(uint16_t));
    bin_file.write((char*) &height, sizeof(uint16_t));
    for (int r = 0; r < map.height(); r++){
        for (int c = 0; c < map.width(); c++){
            bin_file.write((char *) &map[r][c], sizeof(Tile));
        }
    }
}

Map MapBinIO::load(){
    checkNotOpenedError();
    checkFileIssues();
    bin_file.read((char*) &width, sizeof(uint16_t));
    bin_file.read((char*) &height, sizeof(uint16_t)); 
    Map map(width, height);
    for (int r = 0; r < height; r++){
        for (int c = 0; c < width; c++){
            bin_file.read((char*) &map[r][c], sizeof(Tile));
        }
    }
    return map;
}

void MapBinIO::saveTile(Tile& tile, uint16_t x, uint16_t y){
    bin_file.seekp(
        (sizeof(uint16_t) * 2)
        + (width * y)
        + x,
          ios::beg);
    bin_file.write((char*) &tile, sizeof(Tile));
}

Tile MapBinIO::loadTile(uint16_t x, uint16_t y){
    Tile tile;
    bin_file.seekp(
        (sizeof(uint16_t) * 2)
        + (width * y)
        + x,
          ios::beg);
    bin_file.read((char*) &tile, sizeof(Tile));
    return tile;
}

bool MapBinIO::checkOpenedError(){
    if (bin_file.is_open()){
        throw ios_base::failure("File is opened");
        return false;
    }
    return true;
}

bool MapBinIO::checkNotOpenedError(){
    if (!bin_file.is_open()){
        throw ios_base::failure("File is not opened");
        return false;
    }
    return true;
}
bool MapBinIO::checkFileIssues(){
    if (!bin_file){
            bin_file.close();
            throw ios_base::failure("Error opening file");
            return false;
        }
    return true;
}

bool MapBinIO::checkFileExtensionError(const char file_path[]){
    if (filesystem::path(file_path).extension() != FILE_EXTENSION){
            throw filesystem::filesystem_error(
                "Incorrect file extension: " + filesystem::path(file_path).string(),
                FILE_EXTENSION,
                make_error_code(errc::invalid_argument));
            return false;
        }
    return true;
}

bool MapBinIO::checkFileNotExistError(const char file_path[]){
    if (!filesystem::exists(file_path)){
        throw runtime_error(std::string(file_path) + " doesn't exist.");
        return false;
    }
    return true;
}

bool MapBinIO::checkFileExistError(const char file_path[]){
    if (filesystem::exists(file_path)){
        throw runtime_error(std::string(file_path) + " already exist.");
        return false;
    }
    return true;
}
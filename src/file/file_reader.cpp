#include "file_reader.h"
#include "file_checks.h"
#include <filesystem>

void FileReader::open(const char file_path[]){
    checkFileExtensionError(file_path, FILE_EXTENSION);
    checkFileNotExistError(file_path);
    file.open(file_path, std::ios::binary | std::ios::out | std::ios::in);
    checkFileIssues(file);
}

void FileReader::close(){
    checkNotOpenedError(file);
    file.close();
}

bool FileReader::fileOpened(){
    return file.is_open();
};
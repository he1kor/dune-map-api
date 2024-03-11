#include "file_reader.h"
#include <filesystem>

using namespace std;

void FileReader::open(const char file_path[]){
    checkFileExtensionError(file_path);
    checkFileNotExistError(file_path);
    file.open(file_path, ios::binary | ios::out | ios::in);
    checkFileIssues();
}

void FileReader::close(){
    checkNotOpenedError();
    file.close();
}

bool FileReader::fileOpened(){
    return file.is_open();
};

bool FileReader::checkOpenedError(){
    if (file.is_open()){
        throw ios_base::failure("File is opened");
        return false;
    }
    return true;
}

bool FileReader::checkNotOpenedError(){
    if (!file.is_open()){
        throw ios_base::failure("File is not opened");
        return false;
    }
    return true;
}
bool FileReader::checkFileIssues(){
    if (!file){
            file.close();
            throw ios_base::failure("Error opening file");
            return false;
        }
    return true;
}

bool FileReader::checkFileExtensionError(const char file_path[]){
    if (filesystem::path(file_path).extension() != FILE_EXTENSION){
            throw filesystem::filesystem_error(
                "Incorrect file extension: " + filesystem::path(file_path).string(),
                FILE_EXTENSION,
                make_error_code(errc::invalid_argument));
            return false;
        }
    return true;
}

bool FileReader::checkFileNotExistError(const char file_path[]){
    if (!filesystem::exists(file_path)){
        throw runtime_error(std::string(file_path) + " doesn't exist.");
        return false;
    }
    return true;
}

bool FileReader::checkFileExistError(const char file_path[]){
    if (filesystem::exists(file_path)){
        throw runtime_error(std::string(file_path) + " already exist.");
        return false;
    }
    return true;
}
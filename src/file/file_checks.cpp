#include "file_checks.h"
#include <fstream>
#include <filesystem>
#include <ios>

bool checkOpenedError(std::fstream& file){
    if (file.is_open()){
        throw std::ios_base::failure("File is opened");
        return false;
    }
    return true;
}

bool checkNotOpenedError(std::fstream& file){
    if (!file.is_open()){
        throw std::ios_base::failure("File is not opened");
        return false;
    }
    return true;
}
bool checkFileIssues(std::fstream& file){
    if (!file){
            file.close();
            throw std::ios_base::failure("Error opening file");
            return false;
        }
    return true;
}

bool checkFileExtensionError(const char file_path[], const char file_extension[]){
    if (std::filesystem::path(file_path).extension() != file_extension){
            throw std::filesystem::filesystem_error(
                "Incorrect file extension: " + std::filesystem::path(file_path).string(),
                file_extension,
                std::make_error_code(std::errc::invalid_argument));
            return false;
        }
    return true;
}

bool checkFileNotExistError(const char file_path[]){
    if (!std::filesystem::exists(file_path)){
        throw std::runtime_error(std::string(file_path) + " doesn't exist.");
        return false;
    }
    return true;
}

bool checkFileExistError(const char file_path[]){
    if (std::filesystem::exists(file_path)){
        throw std::runtime_error(std::string(file_path) + " already exist.");
        return false;
    }
    return true;
}
bool checkOpenedError(std::ifstream& file){
    if (file.is_open()){
        throw std::ios_base::failure("File is opened");
        return false;
    }
    return true;
}

bool checkNotOpenedError(std::ifstream& file){
    if (!file.is_open()){
        throw std::ios_base::failure("File is not opened");
        return false;
    }
    return true;
}
bool checkFileIssues(std::ifstream& file){
    if (!file){
            file.close();
            throw std::ios_base::failure("Error opening file");
            return false;
        }
    return true;
}
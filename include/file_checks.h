#pragma once
#include <fstream>

bool checkOpenedError(std::fstream& file);
bool checkNotOpenedError(std::fstream& file);
bool checkFileIssues(std::fstream& file);

bool checkOpenedError(std::ifstream& file);
bool checkNotOpenedError(std::ifstream& file);
bool checkFileIssues(std::ifstream& file);

bool checkFileExtensionError(const char file_path[], const char file_extension[]);
bool checkFileExistError(const char file_path[]);
bool checkFileNotExistError(const char file_path[]);
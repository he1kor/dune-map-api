#pragma once
#include <fstream>

class FileReader{
    public:
        bool fileOpened();
        void virtual open(const char file_path[]);
        void virtual close();
        const char* FILE_EXTENSION;

    protected:
        bool checkOpenedError();
        bool checkNotOpenedError();
        bool checkFileIssues();
        bool checkFileExtensionError(const char file_path[]);
        bool checkFileExistError(const char file_path[]);
        bool checkFileNotExistError(const char file_path[]);
        std::fstream file;
};
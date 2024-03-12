#pragma once
#include <fstream>

class FileReader{
    public:
        bool fileOpened();
        void virtual open(const char file_path[]);
        void virtual close();
        const char* FILE_EXTENSION;
        std::fstream file;
};
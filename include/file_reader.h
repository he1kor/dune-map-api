#pragma once
#include <fstream>
/*!
	\brief Abstract class for file access.
*/
class FileReader{
    public:
        /**
         * \brief Returns whether the file is opened.
         * \return True, if file is opened, else False
        */
        bool fileOpened();
        /**
         * \brief Opens file with provided file_path.
         * \param path to the file from this executive file.
        */
        void virtual open(const char file_path[]);
        /**
         * \brief Closes the file.
        */
        void virtual close();
        const char* FILE_EXTENSION;
        std::fstream file;
};
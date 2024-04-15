#pragma once
#include "map.h"
#include "file_reader.h"
#include <fstream>

/*!
	\brief Class for saving and loading map binaries.
*/
class MapBinFileIO : public FileReader {
    public:
        /**
         * \brief Default constructor, late file initialization.
        */
        MapBinFileIO();
        /**
         * \brief File creation constructor, executes create(Map& map, const char file_path[]) method for creating file and saving map to it.
         * \param map Map which should be saved to created file.
         * \param file_path Path where to create a file or open it.
        */
        MapBinFileIO(Map& map, const char file_path[]);
        /**
         * \brief Initializes file from file_path and saves to it the given map. If file already exists, it will be overwritten.
         * \param map Map which should be saved to created file.
         * \param file_path Path where to create a file or open it.
        */
        void create(Map& map, const char file_path[]);
        /**
         * \brief Saves the provided map to the file. If file is not opened, it throws an exception.
         * \param map Map which should be saved to file.
        */
        void save(Map& map);
        /**
         * \brief Loads map from the file and returns it. If file is not opened or has any issues, it throws an exception.
        */
        Map load();
        /**
         * \brief Quick save of single tile to the map. If file is not opened, it throws and exception.
         * \param tile Tile structure to be saved.
         * \param x X coord of the tile.
         * \param y Y coord of the tile.
        */
        void saveTile(Tile& tile, uint16_t x, uint16_t y);
        /**
         * \brief Loads tile from the given coords and returns it. If file is not opened or has any issues, it throws an exception.
        */
        Tile loadTile(uint16_t x, uint16_t y);
    private:
        uint16_t width;
        uint16_t height;
};
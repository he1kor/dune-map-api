/**
 * \file
 * \brief Contains all constants for the library.
*/

#pragma once

namespace d2kmapapi{
    
    /**
     * \brief Determines max height or max width of the map.
    */
    extern const int max_map_size;

    /**
     * \brief Determines what width (size) to consider for tileset line. Required for processing Block and Material search in tileset, when they're placed at different tileset "lines".
    */
    extern const int tileset_width;
}
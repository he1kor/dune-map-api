project(Dune2kMapApi)
add_library(Dune2kMapApi
    structures/map.cpp
    file/file_reader.cpp
    file/file_checks.cpp
    file/map_bin_file_io.cpp
    file/tileset_json_i.cpp
    tileset/palette/material.cpp
    tileset/palette/palette.cpp
    tileset/blocks/compatible_checker.cpp
    tileset/blocks/edge.cpp
    paint/painter.cpp
    )

target_link_libraries(Dune2kMapApi PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(Dune2kMapApi 
                            PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}/../include)
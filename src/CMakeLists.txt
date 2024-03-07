project(Dune2kMapApi)
add_library(Dune2kMapApi
    structures/map.cpp
    file/map_bin_io.cpp
    file/tileset_json_i.cpp
    )

target_link_libraries(Dune2kMapApi PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(Dune2kMapApi PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)
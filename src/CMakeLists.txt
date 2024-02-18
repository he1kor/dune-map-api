project(Dune2kMapApi)
add_library(Dune2kMapApi
    library.cpp
    structures/map.cpp
    file/map_bin_io.cpp
    )
target_include_directories(Dune2kMapApi PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)
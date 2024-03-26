cmake_minimum_required(VERSION 3.6.0)
project(Dune2kMapApi VERSION 0.1.0 LANGUAGES C CXX)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(JSON_Install OFF CACHE INTERNAL "")

include(CPack)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/data/tileset")

set(DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/test/data")

configure_file(${DATA_DIR}/tileset.json ${DEST_DIR}/tileset.json COPYONLY)

add_subdirectory(src)
add_subdirectory(test)
set_property(TARGET Dune2kMapApi PROPERTY CXX_STANDARD 23)
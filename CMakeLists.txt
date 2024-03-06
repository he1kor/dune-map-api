cmake_minimum_required(VERSION 3.6.0)
project(Dune2kMapApi VERSION 0.1.0 LANGUAGES C CXX)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

set(JSON_Install OFF CACHE INTERNAL "")

include(CPack)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_subdirectory(src)
add_subdirectory(test)
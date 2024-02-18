cmake_minimum_required(VERSION 3.6.0)
project(Dune2kMapApi VERSION 0.1.0 LANGUAGES C CXX)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(test)
add_subdirectory(src)

project(Dune2kMapApi)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_DIR}/*.cpp")
add_library(Dune2kMapApi ${SOURCE_FILES})

target_link_libraries(Dune2kMapApi PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(Dune2kMapApi 
                            PUBLIC 
                            ${CMAKE_CURRENT_SOURCE_DIR}/../include)
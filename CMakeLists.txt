cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0048 NEW)
project(sdl2utils VERSION 0.1.0)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#include(CMakeToolsHelperWorkaround)

# SDL2
set(SDL2_BUILDING_LIBRARY true)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(
    "${SDL2_INCLUDE_DIR}/.."
    "${SDL2_IMAGE_INCLUDE_DIR}/.."
    "${SDL2_TTF_INCLUDE_DIR}/.."
)

add_library(
    sdl2utils
    "${CMAKE_SOURCE_DIR}/src/sdl2utils/color_utils.cpp"
    "${CMAKE_SOURCE_DIR}/src/sdl2utils/event_utils.cpp"
    "${CMAKE_SOURCE_DIR}/src/sdl2utils/exceptions.cpp"
)
target_include_directories(sdl2utils PUBLIC "${CMAKE_SOURCE_DIR}/include")

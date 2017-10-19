cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0048 NEW)
project(sdl2utils VERSION 0.1.0)

# Require C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Source & header files
set(CPP_FILES_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src/sdl2utils")
set(
    CPP_FILES
    
    "${CPP_FILES_ROOT}/color_utils.cpp"
    "${CPP_FILES_ROOT}/event_utils.cpp"
    "${CPP_FILES_ROOT}/exceptions.cpp"
)
set(H_FILES_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include/sdl2utils")
set(
    H_FILES
    
    "${H_FILES_ROOT}/color_utils.h"
    "${H_FILES_ROOT}/deleters.h"
    "${H_FILES_ROOT}/event_utils.h"
    "${H_FILES_ROOT}/exceptions.h"
    "${H_FILES_ROOT}/guards.h"
    "${H_FILES_ROOT}/pointers.h"
    "${H_FILES_ROOT}/raii.h"

    "${H_FILES_ROOT}/raii/ScopedRenderDrawColor.h"
    "${H_FILES_ROOT}/raii/ScopedRenderTarget.h"
    "${H_FILES_ROOT}/raii/ScopedSDLCore.h"
    "${H_FILES_ROOT}/raii/ScopedSDLImageExt.h"
    "${H_FILES_ROOT}/raii/ScopedSDLTtfExt.h"
)

#include(CMakeToolsHelperWorkaround)

# SDL2
set(SDL2_BUILDING_LIBRARY true)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Boost
find_package(Boost COMPONENTS REQUIRED)

include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR}
)

add_library(
    sdl2utils
    ${CPP_FILES}
)
target_include_directories(sdl2utils PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

install(TARGETS sdl2utils DESTINATION lib)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/sdl2utils" DESTINATION include)

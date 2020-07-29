cmake_minimum_required(VERSION 3.16)
project(LEDStripAnimationLibrary)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(AnimationLibrary Animation.cpp ColorRGB.cpp)

add_subdirectory(AnimationPreview)

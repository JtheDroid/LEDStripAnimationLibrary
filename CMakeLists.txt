cmake_minimum_required(VERSION 3.16)
project(LEDStripAnimations)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(LEDStripAnimations main.cpp Animation.h TimedAnimation.h FunctionAnimationDisplay.h FiniteAnimation.h AnimationPreviewSDL.h SDLcleanup.h)
target_link_libraries(LEDStripAnimations ${SDL2_LIBRARIES})

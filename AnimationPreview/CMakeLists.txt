find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(AnimationPreview AnimationPreviewSDL.cpp SDLcleanup.h)
target_include_directories(AnimationPreview PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(AnimationPreview ${SDL2_LIBRARIES} AnimationLibrary)

add_executable(LEDStripAnimations main.cpp)
target_include_directories(LEDStripAnimations PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(LEDStripAnimations AnimationLibrary AnimationPreview)
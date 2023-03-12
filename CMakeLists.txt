cmake_minimum_required(VERSION 3.24)
project(c__raytracing)

set(CMAKE_CXX_STANDARD 17)

add_executable(c__raytracing main.cpp consts.h)

set(SIMPLE2D_IBS -lsimple2d -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -lGL -lm -lSDL2_image -lSDL2_mixer -lSDL2_ttf)
target_link_libraries(c__raytracing ${SIMPLE2D_IBS})
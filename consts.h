//
// Created by tructruc00 on 12/03/23.
//
#include <simple2d.h>
#include "math.h"
#ifndef C__RAYTRACING_CONSTS_H
#define C__RAYTRACING_CONSTS_H

#endif //C__RAYTRACING_CONSTS_H


// Structs -------------------------------------------------------------------------------------------------------------

struct Color {
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

// Constants -----------------------------------------------------------------------------------------------------------

const int WINDOW_HEIGHT= 500;
const int WINDOW_WIDTH=500;

const int map_width=10;
const int map_height=10;
const int map_block_pixel_size=50;
const int map[]{
        1,1,1,1,1,1,1,1,1,1,
        1,0,1,0,0,0,0,0,0,1,
        1,0,1,0,0,0,0,0,0,1,
        1,0,1,0,0,0,0,0,0,1,
        1,0,1,0,0,0,0,1,0,1,
        1,0,1,0,1,1,1,0,0,1,
        1,0,1,0,1,0,0,0,0,1,
        1,0,0,0,1,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1

};

const float PLAYER_FOV = 1.047197551;


const Color RED = {1,0,0,1};
const Color GREEN = {0, 1, 0, 1};
const Color BLUE = {0, 0, 1, 1};
const Color BLACK = {0,0,0,1};
const Color WHITE = {1, 1, 1, 1};
const Color GREY = {0.5,0.5,0.5,1};

const float PI_2 = M_PI/2;
const float PI1 = M_PI;
const float PI1_2= M_PI+M_PI/2;
const float PI2 = M_PI*2;
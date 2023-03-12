#include <iostream>
#include "consts.h"


// Global Variables ----------------------------------------------------------------------------------------------------

float player_x = 1.5;
float player_y = 1.5;
float player_angle=1;

// Functions -----------------------------------------------------------------------------------------------------------
/**
 * Draw a line on the window
 * @param x1 x of the 1rst point
 * @param y1 y of the forst point
 * @param x2 x of the second point
 * @param y2 y of the second point
 * @param width width of the line
 * @param color color of the line
 */
void drawline(GLfloat x1,GLfloat y1, GLfloat x2, GLfloat y2, GLfloat width, Color color){
    S2D_DrawLine(x1, y1, x2, y2,width,
                 color.r, color.g, color.b, color.a,
                 color.r, color.g, color.b, color.a,
                 color.r, color.g, color.b, color.a,
                 color.r, color.g, color.b, color.a);
}

/**
 * Draw a plain recctangle onto the screen
 * @param x1 x of the top left poinr
 * @param y1 y of the top left point
 * @param x2 x of the bottom right point
 * @param y2 y of the bottom right point
 * @param color color of the retangle
 */
void drawrect(GLfloat x1,GLfloat y1, GLfloat x2, GLfloat y2, Color color){
    S2D_DrawQuad(x1, y1, color.r, color.g, color.b, color.a,
                 x1, y2, color.r, color.g, color.b, color.a,
                 x2, y2, color.r, color.g, color.b, color.a,
                 x2, y1, color.r, color.g, color.b, color.a);
}

void search_intersect(float px, float py, float angle, float* pos[2]){
    float x,y=0;


    if (angle>=0 && angle < PI_2){
        px += 0.01;
        py += 0.01;
        if (tan(PI_2-angle) * ((int)py + 1 - py) < ((int)px + 1 - px)) {
            x = tan(PI_2 - angle) * ((int) py + 1 - py) + px;
            y = (int)py+1;
            //std::cout << "x : " << x << ", y : " << y << std::endl;
        }
        else {
            x = (int)px+1;
            y = tan(angle) * ((int) px + 1 - px) + py;
            //std::cout << "x : " << x << ", y : " << y << std::endl;
        }
    }
    if (angle>=PI_2 && angle < PI1){
        px -= 0.01;
        py += 0.01;
        if (tan(PI_2 - angle) * ( (int)py- py + 1 ) > ((int)px-px)) {
            x = tan(PI_2 - angle) * ((int) py + 1 - py) + px;
            y = (int)py+1;
            //std::cout << "x : " << x << ", y : " << y << std::endl;
        }
        else {
            x = (int)(px-0.01);
            y = tan(angle) * ((int) (px-0.01) - px) + py;
            //std::cout << "x : " << x << ", y : " << y << std::endl;
        }
    }
    if (angle>=PI1 && angle < PI1_2) {
        px -= 0.01;
        py -= 0.01;
        if (tan(PI_2 - angle) * ((int)py - py) > ( (int)px- px)) {
            x = tan(PI_2 - angle) * ((int)py - py) + px;
            y = (int)py;
            //std::cout << "x : " << x << ", y : " << y << std::endl;
        }
        else {
            x = (int)px;
            y = tan(angle) * ((int) px - px) + py;
            //std::cout << "x : " << x << ", y : " << y << std::endl;
        };
    }
    if (angle>=PI1_2 && angle < PI2) {
        px += 0.01;
        py -= 0.01;
        if (tan(PI_2 - angle) * ((int)py - py) < ( (int)px- px+1)){
            x = tan(PI_2 - angle) * ((int)py - py) + px;
            y = (int)py;
            //std::cout << "x : " << x << ", y : " << y << std::endl;
        }
        else {
            x = (int)px+1;
            y = tan(angle) * ((int) px + 1 - px) + py;
            //std::cout << "x : " << x << ", y : " << y << std::endl;
        }
    }

    //drawrect(x*map_block_pixel_size-5,y* map_block_pixel_size-5, x*map_block_pixel_size+5, y*map_block_pixel_size+5, GREEN );

    pos[0] = &x;
    pos[1] = &y;
}

void dist_wall(float angle){
    float* pos[2];

    search_intersect(player_x, player_y, angle, pos);
    while(map[(int)*pos[0]+((int)*pos[1]*map_width)]== 0){
        search_intersect(*pos[0], *pos[1], angle, pos);
    }

    drawrect(*pos[0]*map_block_pixel_size-5,*pos[1]* map_block_pixel_size-5, *pos[0]*map_block_pixel_size+5, *pos[1]*map_block_pixel_size+5, BLUE );

    //std::cout << pos[0] << "; " << pos[1] << "; " << map[(int)*pos[0]+((int)*pos[1]*map_width)] << std::endl;

}
// Window spécific functions -------------------------------------------------------------------------------------------

void on_key(S2D_Event e) {
    // Check `e.key` for the key being interacted with

    switch (e.type) {
        case S2D_KEY_DOWN:

            break;

        case S2D_KEY_HELD:
            if (strcmp(e.key, "Right")==0) {
                player_angle += 0.03;

                if (player_angle > PI2) player_angle -= PI2; // Prevent angle overflow
            }
            if (strcmp(e.key,"Left")==0){
                player_angle-=0.03;

                if (player_angle < 0) player_angle += PI2; //prevent angle overflow
            }
            if (strcmp(e.key, "Up")==0){
                player_x +=cos(player_angle)*0.05;
                player_y +=sin(player_angle)*0.05;
            }
            if (strcmp(e.key, "Down")==0){
                player_x -=cos(player_angle)*0.05;
                player_y -=sin(player_angle)*0.05;
            }
            break;

        case S2D_KEY_UP:
            // Key was released
            break;
    }
}
void render() {
    drawrect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GREY);

    for (int x = 0; x < map_width; ++x) {
        for (int y = 0; y < map_height; ++y) {
            if (map[x+(y*map_width)]){
                drawrect(x*map_block_pixel_size+1, y*map_block_pixel_size+1, (x+1)*map_block_pixel_size-1, (y+1)*map_block_pixel_size-1, WHITE);
            } else{
                drawrect(x*map_block_pixel_size+1, y*map_block_pixel_size+1, (x+1)*map_block_pixel_size-1, (y+1)*map_block_pixel_size-1, BLACK);
            }
        }
    }

    drawrect(player_x*map_block_pixel_size-5,
             player_y*map_block_pixel_size-5,
             player_x*map_block_pixel_size+5,
             player_y*map_block_pixel_size+5,
             RED);

    drawline(player_x*map_block_pixel_size,
             player_y*map_block_pixel_size,
             player_x*map_block_pixel_size+ cos(player_angle)*20,
             player_y*map_block_pixel_size+ sin(player_angle)*20,
             3,
             RED);

    float* pos[2];


    for (int i = 0; i < 60; i+=1) {
        dist_wall(player_angle-0.523598776+i*0.017453293);
    }


}





void update() {

}


int main() {

    S2D_Window *window = S2D_CreateWindow(
            "RayCasting", WINDOW_WIDTH, WINDOW_HEIGHT, update, render, 0
    );
    window->on_key = on_key;
    S2D_Show(window);
    return 0;
}
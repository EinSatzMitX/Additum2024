#include "../include/fb.h"
#include "../include/io.h"
#include "../include/breakout.h"

// The screen
#define WIDTH         1920
#define HEIGHT        1080
#define MARGIN        30
#define VIRTWIDTH     (WIDTH-(2*MARGIN))
#define FONT_BPG      8

// Gameplay
#define GRIDSIZEX     15
#define GRIDSIZEY     15
#define GRIDCELLSIZEX 20
#define GRIDCELLSIZEY 20



enum {
    OBJ_NONE   = 0,
    OBJ_APPLE  = 1,
    OBJ_SNAKE_HEAD = 2,
    OBJ_SNAKE_BODY   = 3
};

unsigned int numobjssnake = 0;
struct Object *objectssnake = (struct Object *)SAFE_ADDRESS;
struct Object *apple;
struct Object *snake_head;
struct Object *snake_body;

void init_apple()
{
    int appleradius = 20;

    drawCircle(WIDTH/2, HEIGHT/2, appleradius, 0x55, 1);

    objectssnake[numobjssnake].type = OBJ_APPLE;
    objectssnake[numobjssnake].x = (WIDTH/2) - appleradius;
    objectssnake[numobjssnake].y = (HEIGHT/2) - appleradius;
    objectssnake[numobjssnake].width = appleradius * 2;
    objectssnake[numobjssnake].height = appleradius * 2;
    objectssnake[numobjssnake].alive = 1;
    apple = &objectssnake[numobjssnake];
    numobjssnake++;
}


void init_snake(){
    struct Object *foundObject;
    unsigned char ch = 0;

    int lives = 1;
    
    int score = 0;
    
    int velocity_x = 1;
    int velocity_y = 3;

    init_apple();
    drawScoreboard(score, lives);
}
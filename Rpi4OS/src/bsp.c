/*
#include "../include/bsp.h"
#include "../include/fb.h"
#include "../include/math.h"

#define WIDTH         1920
#define HEIGHT        1080
#define MARGIN        30
#define VIRTWIDTH     (WIDTH-(2*MARGIN))


typedef struct 
{
 int fr1,fr2;           //frame 1 frame 2, to create constant frame rate
}time; time T;

typedef struct 
{
 int w,s,a,d;           //move up, down, left, right
 int sl,sr;             //strafe left, right 
 int m;                 //move up, down, look up, down
}keys; keys K;

typedef struct 
{
    float cos[360];
    float sin[360];
}math;  math M;

typedef struct{
    int x, y, z;    // player position down up
    int a;          // player angle of rotation left right
    int l;          // variable to look up and down
}player;   player P;

void move_player(){
    // move up, down, left, right
    if (getUart() == 'a' ) {
        P.a -= 4; 
        if(P.a< 0) {
            P.a += 360;
        }
    }
    if (getUart() == 'd' ) {
        P.a += 4; 
        if(P.a>359) {
            P.a -= 360;
        }
    }
    int dx = M.sin[P.a] * 10.0;
    int dy = M.cos[P.a] * 10.0;
    if (getUart() == 'w' ) {
        P.x += dx;
        P.y += dy;
    }
    if (getUart() == 's' ) {
        P.x -= dx;
        P.y -= dy;
    }
    // move up, move down, look up, look down
    
    if (getUart() == 'a' && getUart() == 'm') 
    if (getUart() == 'd' && getUart() == 'm') 
    if (getUart() == 'w' && getUart() == 'm') 
    if (getUart() == 's' && getUart() == 'm') 
    
}

void draw_3D(){
    int wx[4], wy[4], wz[4];
    float CS = M.cos[P.a], SN = M.sin[P.a];
    // offset bottom 2 points by player
    int x1 = 40 - P.x, y1 = 10 - P.y;
    int x2 = 40 - P.x, y2 = 290 - P.y;

    // world position
    wx[0] = x1 * CS - y1 * SN;
    wx[1] = x2 * CS - y2 * SN;
    // world Y position (depth)
    wy[0] = y1 * CS + x1 * SN;
    wy[1] = y2 * CS + x1 * SN;
    // world Z Height
    wz[0] = 0 - P.z + ((P.l*wy[0])/32.0);
    wz[1] = 0 - P.z + ((P.l*wy[1])/32.0);

    // screen x, y positions
    wx[0] = wx[0] * 200 / wy[0] + WIDTH;
    wy[0] = wz[0] * 200 / wy[0] + HEIGHT;
    wx[1] = wx[1] * 200 / wy[1] + WIDTH;
    wy[1] = wz[1] * 200 / wy[1] + HEIGHT;
    // draw points
    if(wx[0]>0 && wx[0]<WIDTH && wy[0] > 0 && wy[0]<HEIGHT){
        drawPixel(wx[0], wy[0], 5);
    }
    if(wx[1]>0 && wx[1]<WIDTH && wy[1]>0 && wy[1]< HEIGHT){
        drawPixel(wx[1], wy[1], 4);
    }
}

void init_bsp()
{
    int ALIVE = 1;

    drawString(10, 10, "entered bsp function!", 4, 4);

    int x = 0;

    for (x; x < 360; x++){
        M.cos[x] = cosine(x / 180.0 * PI);
    }

    drawString(20, 20, "passed cosine loop", 4, 4);

    // init player
    P.x = 70;
    P.y = -110;
    P.z = 20;
    P.a = 0;
    P.l = 0;

    while (!getUart());

    drawPixel(100, 100, 5);

    while(ALIVE != 0){
        drawChar('b', 10, 10, 5, 3);
        draw_3D();
        drawChar('c', 10, 10, 5, 3);
        move_player();
        drawChar('d', 10, 10, 5, 3);
    }
}
*/
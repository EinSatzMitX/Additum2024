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
#define SNAKE_SPEED   2
struct Object grid[GRIDSIZEX][GRIDCELLSIZEY];

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
struct Object *snake_body_parts[224];
unsigned int numsnakebodyparts = 1;


void init_grid(){
    for (int i = 0; i < GRIDCELLSIZEX; i++){
        for (int j = 0; j < GRIDCELLSIZEY; j++){
            grid[i][j].type = OBJ_NONE;
            grid[i][j].x = i * GRIDCELLSIZEX;
            grid[i][j].y = i * GRIDCELLSIZEY;
            grid[i][j].height = GRIDCELLSIZEY;
            grid[i][j].width = i * GRIDCELLSIZEX;
        }
    }
}

void init_apple()
{

    drawCircle(WIDTH/2, HEIGHT/2, GRIDCELLSIZEX, 0x55, 1);

    objectssnake[numobjssnake].type = OBJ_APPLE;
    objectssnake[numobjssnake].x = (WIDTH/2) - GRIDCELLSIZEX;
    objectssnake[numobjssnake].y = (HEIGHT/2) - GRIDCELLSIZEX;
    objectssnake[numobjssnake].width = GRIDCELLSIZEX * 2;
    objectssnake[numobjssnake].height = GRIDCELLSIZEX * 2;
    objectssnake[numobjssnake].alive = 1;
    apple = &objectssnake[numobjssnake];
    numobjssnake++;
}

void init_snake(){
    grid[5][5].alive = 1;
    grid[5][5].type = OBJ_SNAKE_HEAD;

    drawCircle(grid[5][5].x, grid[5][5].y, GRIDCELLSIZEX, 0x02, 1);
}

void init_snake_Game(){


    unsigned char ch = 0;

    int lives = 1;
    
    int score = 0;
    
    //int velocity_x = 1;
    //int velocity_y = 3;

    init_grid();
    init_snake();
    init_apple();


    drawScoreboard(score, lives);

    while (!getUart());

        
    while (lives > 0 && sizeof(snake_body_parts) < 224) {
       // Get any waiting input and flush the buffer
       if ( ( ch = getUart() ) ) {
        /*
	  if (ch == 'l') if (paddle->x + paddle->width + (paddle->width / 2) <= WIDTH-MARGIN) moveObject(paddle, paddle->width / 2, 0);
	  if (ch == 'h') if (paddle->x >= MARGIN+(paddle->width / 2)) moveObject(paddle, -(paddle->width / 2), 0);
      */
        if (ch =='l'){

            for (int i = 0; i < sizeof(snake_body_parts); i++)
            {
                snake_body_parts[i]->x;
            }
            if (snake_head->x > GRIDCELLSIZEX - SNAKE_SPEED){
                moveObject(snake_head, SNAKE_SPEED, 0);
            }
            else if (snake_head->x < 0 + SNAKE_SPEED) {
                moveObject(snake_head, SNAKE_SPEED, 0);
            }
        }
       }
       /*
       uart_loadOutputFifo();

       // Are we going to hit anything?
       foundObject = detectCollision(ball, velocity_x, velocity_y);

       if (foundObject) {
          if (foundObject == paddle) {
             velocity_y = -velocity_y;
	     // Are we going to hit the side of the paddle
	     if (ball->x + ball->width + velocity_x == paddle->x || ball->x + velocity_x == paddle->x + paddle->width) velocity_x = -velocity_x;
          } else if (foundObject->type == OBJ_BRICK) {
             removeObject(foundObject);
             velocity_y = -velocity_y;
             bricks--;
             points++;
             drawScoreboard(points, lives);
          }
       }

       wait_msec(4000); // Wait a little...
       moveObject(ball, velocity_x, velocity_y);

       // Check we're in the game arena still
       if (ball->x + ball->width >= WIDTH-MARGIN) {
          velocity_x = -velocity_x;
       } else if (ball->x <= MARGIN) {
          velocity_x = -velocity_x;
       } else if (ball->y + ball->height >= HEIGHT-MARGIN) {
          lives--;

	  removeObject(ball);
	  removeObject(paddle);

          initBall();
          initPaddle();
          drawScoreboard(points, lives);
       } else if (ball->y <= MARGIN) {
          velocity_y = -velocity_y;
       }
       */
    }

    int zoom = WIDTH/192;
    int strwidth = 10 * FONT_BPG * zoom;
    int strheight = FONT_BPG * zoom;

    if (numsnakebodyparts  == 254) drawString((WIDTH/2)-(strwidth/2), (HEIGHT/2)-(strheight/2), "Well done!", 0x02, zoom);
    else drawString((WIDTH/2)-(strwidth/2), (HEIGHT/2)-(strheight/2), "Game over!", 0x04, zoom);
    
    
}
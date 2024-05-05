struct Object
{
    unsigned int type;
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
    unsigned char alive;
};

void removeObject(struct Object *object);
void moveObject(struct Object *object, int xoff, int yoff);
struct Object *detectCollision(struct Object *with, int xoff, int yoff);
//unsigned char getUart();
/*
void initBricks();
void initBall();
void initPaddle();
*/
void drawScoreboard(int score, int lives);

void clearScreen();
void initBreakout();
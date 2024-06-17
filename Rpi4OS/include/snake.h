
typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point position;
    int direction;
} SnakeSegment;

typedef struct {
    SnakeSegment segments[100]; // Maximum length of the snake
    int length;
    int direction;
} Snake;

typedef struct {
    Point position;
} Food;

void initializeGame();
void generateFood();
void drawGame();
void updateGame();
void handleInput(unsigned char input);
int checkCollision(Point p);
void gameOver();
void init_snake();
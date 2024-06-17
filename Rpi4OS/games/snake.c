#include "../include/fb.h"
#include "../include/io.h"
#include "../include/snake.h"
#include "../include/math.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SNAKE_SIZE 5
#define FOOD_SIZE 5

// Directions
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

Snake snake;
Food food;
int game_over = 0;

// Function prototypes
void initializeGame();
void generateFood();
void drawGame();
void updateGame();
void handleInput(unsigned char input);
int checkCollision(Point p);
void gameOver();

void initializeGame() {
    // Initialize PRNG seed with a value
    lcg_srand(1234); // Or use a more variable value

    // Initialize snake
    snake.length = 1;
    snake.segments[0].position.x = SCREEN_WIDTH / 2;
    snake.segments[0].position.y = SCREEN_HEIGHT / 2;
    snake.direction = RIGHT;
    
    // Generate first food
    generateFood();
    drawString(100, 100, "generating food", 4, 3);
}

void generateFood() {
    food.position.x = (lcg_rand() % (SCREEN_WIDTH / FOOD_SIZE)) * FOOD_SIZE;
    food.position.y = (lcg_rand() % (SCREEN_HEIGHT / FOOD_SIZE)) * FOOD_SIZE;
}

void drawGame() {
    // Clear screen
    drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 1);
    
    // Draw snake
    for (int i = 0; i < snake.length; i++) {
        drawRect(snake.segments[i].position.x, snake.segments[i].position.y,
                 snake.segments[i].position.x + SNAKE_SIZE,
                 snake.segments[i].position.y + SNAKE_SIZE, 1, 1);
    }
    
    // Draw food
    drawRect(food.position.x, food.position.y,
             food.position.x + FOOD_SIZE, food.position.y + FOOD_SIZE, 2, 1);
}

void updateGame() {
    // Move snake
    Point newHead = snake.segments[0].position;
    
    switch (snake.direction) {
        case UP:    newHead.y -= SNAKE_SIZE; break;
        case DOWN:  newHead.y += SNAKE_SIZE; break;
        case LEFT:  newHead.x -= SNAKE_SIZE; break;
        case RIGHT: newHead.x += SNAKE_SIZE; break;
    }
    
    // Debug: Draw new head position
    drawRect(newHead.x, newHead.y, newHead.x + SNAKE_SIZE, newHead.y + SNAKE_SIZE, 3, 1);
    
    // Check collision with walls
    if (newHead.x < 0 || newHead.x >= SCREEN_WIDTH || newHead.y < 0 || newHead.y >= SCREEN_HEIGHT) {
        gameOver();
        return;
    }
    
    // Check collision with self
    if (checkCollision(newHead)) {
        gameOver();
        return;
    }
    
    // Move segments
    for (int i = snake.length - 1; i > 0; i--) {
        snake.segments[i].position = snake.segments[i - 1].position;
    }
    snake.segments[0].position = newHead;
    
    // Check collision with food
    if (newHead.x == food.position.x && newHead.y == food.position.y) {
        snake.length++;
        generateFood();
    }
}

void handleInput(unsigned char input) {
    drawString(10, 10, "Input: ", 1, 1);
    drawChar(input, 60, 10, 1, 1); // Display the input character for debugging
    
    switch (input) {
        case 'w': if (snake.direction != DOWN) snake.direction = UP; break;
        case 's': if (snake.direction != UP) snake.direction = DOWN; break;
        case 'a': if (snake.direction != RIGHT) snake.direction = LEFT; break;
        case 'd': if (snake.direction != LEFT) snake.direction = RIGHT; break;
    }
}

int checkCollision(Point p) {
    for (int i = 0; i < snake.length; i++) {
        if (snake.segments[i].position.x == p.x && snake.segments[i].position.y == p.y) {
            return 1;
        }
    }
    return 0;
}

void gameOver() {
    game_over = 1;
    drawString(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2, "GAME OVER", 1, 2);
}

// Main game loop
void init_snake() {

    // Wait to see the test drawing
    wait_msec(5000);

    initializeGame();
    
    while (!game_over) {
        drawGame();
        updateGame();
        // Handle input here (you will need to implement input handling)
        uart_loadOutputFifo();
        unsigned char input = getUart(); // For example
        handleInput(input);
        
        // Delay to control game speed
        wait_msec(300);
    }
}
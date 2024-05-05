#include "../include/fb.h"
#include "../include/io.h"
//#include "../include/snake.h"
#include "../include/breakout.h"
#include "../include/bsp.h"
#include "../include/math.h"

void main()
{
    uart_init();
    fb_init();
    //init_snake_Game();
    drawChar('a', 10, 10, 5, 3);
    init_bsp();
    drawChar('b', 10, 10, 5, 3);
    while(1) {
        updateTerminalInput(0, 0, 0x15, 5);
    }
}
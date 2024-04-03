#include "../include/fb.h"
#include "../include/io.h"
#include "../include/snake.h"

void main()
{
    uart_init();
    fb_init();
    init_snake();
    
    while(1) {
        updateTerminalInput(0, 0, 0x15, 5);
    }
}
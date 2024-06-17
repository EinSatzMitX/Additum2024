#include "../include/fb.h"
#include "../include/io.h"
//#include "../include/snake.h"
#include "../include/breakout.h"
//#include "../include/bsp.h"
#include "../include/math.h"
#include "../include/util.h"
#include "../include/commands.h"

void main()
{
    uart_init();
    fb_init();
    init_Commands();

    cmd_hi();

    // Terminal section

    while(1){
        uart_update_Terminal(1920, 1080);
        uart_clear_Terminal_Queue();
    }

}
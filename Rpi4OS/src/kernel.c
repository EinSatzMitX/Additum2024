#include "fb.h"
#include "io.h"
#include "breakout.h"

// The screen
#define WIDTH         1920
#define HEIGHT        1080
#define MARGIN        30
#define VIRTWIDTH     (WIDTH-(2*MARGIN))
#define FONT_BPG      8


void main()
{
    initBreakout();
    clearScreen();
    
    while(1) {
        updateTerminalInput(0, 0, 0x15, 5);
    }
}
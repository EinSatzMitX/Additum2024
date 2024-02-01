#include "fb.h"
#include "io.h"

void main()
{
    uart_init();
    uart_writeText("test");
    uart_detectInput();
    uart_writeText("test 2");
}
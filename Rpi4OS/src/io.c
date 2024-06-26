#include "../include/io.h"
#include "../include/fb.h"
#include "../include/commands.h"

// GPIO

enum {
    GPFSEL0         = PERIPHERAL_BASE + 0x200000,
    GPSET0          = PERIPHERAL_BASE + 0x20001C,
    GPCLR0          = PERIPHERAL_BASE + 0x200028,
    GPPUPPDN0       = PERIPHERAL_BASE + 0x2000E4
};

enum {
    GPIO_MAX_PIN       = 53,
    GPIO_FUNCTION_OUT  = 1,
    GPIO_FUNCTION_ALT5 = 2,
    GPIO_FUNCTION_ALT3 = 7
};

enum {
    Pull_None = 0,
    Pull_Down = 1, // Are down and up the right way around?
    Pull_Up = 2
};

void mmio_write(long reg, unsigned int val) { *(volatile unsigned int *)reg = val; }
unsigned int mmio_read(long reg) { return *(volatile unsigned int *)reg; }

unsigned int gpio_call(unsigned int pin_number, unsigned int value, unsigned int base, unsigned int field_size, unsigned int field_max) {
    unsigned int field_mask = (1 << field_size) - 1;
  
    if (pin_number > field_max) return 0;
    if (value > field_mask) return 0; 

    unsigned int num_fields = 32 / field_size;
    unsigned int reg = base + ((pin_number / num_fields) * 4);
    unsigned int shift = (pin_number % num_fields) * field_size;

    unsigned int curval = mmio_read(reg);
    curval &= ~(field_mask << shift);
    curval |= value << shift;
    mmio_write(reg, curval);

    return 1;
}

unsigned int gpio_set     (unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPSET0, 1, GPIO_MAX_PIN); }
unsigned int gpio_clear   (unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPCLR0, 1, GPIO_MAX_PIN); }
unsigned int gpio_pull    (unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPPUPPDN0, 2, GPIO_MAX_PIN); }
unsigned int gpio_function(unsigned int pin_number, unsigned int value) { return gpio_call(pin_number, value, GPFSEL0, 3, GPIO_MAX_PIN); }

void gpio_useAsAlt3(unsigned int pin_number) {
    gpio_pull(pin_number, Pull_None);
    gpio_function(pin_number, GPIO_FUNCTION_ALT3);
}

void gpio_useAsAlt5(unsigned int pin_number) {
    gpio_pull(pin_number, Pull_None);
    gpio_function(pin_number, GPIO_FUNCTION_ALT5);
}

void gpio_initOutputPinWithPullNone(unsigned int pin_number) {
    gpio_pull(pin_number, Pull_None);
    gpio_function(pin_number, GPIO_FUNCTION_OUT);
}

void gpio_setPinOutputBool(unsigned int pin_number, unsigned int onOrOff) {
    if (onOrOff) {
        gpio_set(pin_number, 1);
    } else {
        gpio_clear(pin_number, 1);
    }
}

// UART

enum {
    AUX_BASE        = PERIPHERAL_BASE + 0x215000,
    AUX_IRQ         = AUX_BASE,
    AUX_ENABLES     = AUX_BASE + 4,
    AUX_MU_IO_REG   = AUX_BASE + 64,
    AUX_MU_IER_REG  = AUX_BASE + 68,
    AUX_MU_IIR_REG  = AUX_BASE + 72,
    AUX_MU_LCR_REG  = AUX_BASE + 76,
    AUX_MU_MCR_REG  = AUX_BASE + 80,
    AUX_MU_LSR_REG  = AUX_BASE + 84,
    AUX_MU_MSR_REG  = AUX_BASE + 88,
    AUX_MU_SCRATCH  = AUX_BASE + 92,
    AUX_MU_CNTL_REG = AUX_BASE + 96,
    AUX_MU_STAT_REG = AUX_BASE + 100,
    AUX_MU_BAUD_REG = AUX_BASE + 104,
    AUX_UART_CLOCK  = 500000000,
    UART_MAX_QUEUE  = 16 * 1024
};

#define AUX_MU_BAUD(baud) ((AUX_UART_CLOCK/(baud*8))-1)

unsigned char uart_output_queue[UART_MAX_QUEUE];
unsigned int uart_output_queue_write = 0;
unsigned int uart_output_queue_read = 0;

void uart_init() {
    mmio_write(AUX_ENABLES, 1); //enable UART1
    mmio_write(AUX_MU_IER_REG, 0);
    mmio_write(AUX_MU_CNTL_REG, 0);
    mmio_write(AUX_MU_LCR_REG, 3); //8 bits
    mmio_write(AUX_MU_MCR_REG, 0);
    mmio_write(AUX_MU_IER_REG, 0);
    mmio_write(AUX_MU_IIR_REG, 0xC6); //disable interrupts
    mmio_write(AUX_MU_BAUD_REG, AUX_MU_BAUD(112500));
    gpio_useAsAlt5(14);
    gpio_useAsAlt5(15);
    mmio_write(AUX_MU_CNTL_REG, 3); //enable RX/TX
}

unsigned int uart_isOutputQueueEmpty() {
    return uart_output_queue_read == uart_output_queue_write;
}

unsigned int uart_isReadByteReady()  { return mmio_read(AUX_MU_LSR_REG) & 0x01; }
unsigned int uart_isWriteByteReady() { return mmio_read(AUX_MU_LSR_REG) & 0x20; }

unsigned char uart_readByte() {
    while (!uart_isReadByteReady());
    return (unsigned char)mmio_read(AUX_MU_IO_REG);
}

void uart_writeByteBlockingActual(unsigned char ch) {
    while (!uart_isWriteByteReady()); 
    mmio_write(AUX_MU_IO_REG, (unsigned int)ch);
}

void uart_loadOutputFifo() {
    while (!uart_isOutputQueueEmpty() && uart_isWriteByteReady()) {
        uart_writeByteBlockingActual(uart_output_queue[uart_output_queue_read]);
        uart_output_queue_read = (uart_output_queue_read + 1) & (UART_MAX_QUEUE - 1); // Don't overrun
    }
}

void uart_writeByteBlocking(unsigned char ch) {
    unsigned int next = (uart_output_queue_write + 1) & (UART_MAX_QUEUE - 1); // Don't overrun

    while (next == uart_output_queue_read) uart_loadOutputFifo();

    uart_output_queue[uart_output_queue_write] = ch;
    uart_output_queue_write = next;
}

void uart_writeText(char *buffer) {
    while (*buffer) {
       if (*buffer == '\n') uart_writeByteBlockingActual('\r');
       uart_writeByteBlockingActual(*buffer++);
    }
}

void uart_drainOutputQueue() {
    while (!uart_isOutputQueueEmpty()) uart_loadOutputFifo();
}

void uart_update() {
    uart_loadOutputFifo();

    if (uart_isReadByteReady()) {
       unsigned char ch = uart_readByte();
       if (ch == '\r') uart_writeText("\n"); else uart_writeByteBlocking(ch);
    }
}

struct Terminal
{
    unsigned char Input[256]; // This number is completely made up and doesn't serve any purpose, feel free to change whenever it's needed
    int currentIndex;
    int currentX;
    int currentY;
    int zoom;
};

struct Terminal Terminal;

void uart_clear_Terminal_Queue(){
    for (int i = 0; i < Terminal.currentIndex; i++){
        Terminal.Input[i] = 0;
    }
    Terminal.currentIndex = 0;
}

void uart_reset_Terminal(){
    uart_clear_Terminal_Queue();
    Terminal.currentX = 0;
    Terminal.currentY = 0;
    Terminal.zoom = 2;

    // vvv Actual Footage of me being an absolute moron vvv
    //Terminal.zoom = 0;
}

void uart_add_char_to_Terminal_Input(char c){
    Terminal.Input[Terminal.currentIndex] = c;
    Terminal.currentIndex++;
}

void uart_update_Terminal(int width, int height){
    int pressed_Enter = 0;
    while (!pressed_Enter)
    {
            uart_loadOutputFifo();

    if (uart_isReadByteReady()) {
        unsigned char ch = uart_readByte();
        if (ch == '\r'){
            drawChar('\n', Terminal.currentX, Terminal.currentY, 2, Terminal.zoom);

            //Add the letter to the Terminal Input. This line of code is important and you shouldn't forget something as necessary as this...
            Terminal.Input[Terminal.currentIndex] = '\n';
            Terminal.currentIndex++;
            
            Terminal.currentY += (Terminal.zoom * 8);
            Terminal.currentX = 0;
            pressed_Enter = 1;
            break;
        }
        else if(ch == 0b01111111){

            /* Input logic (works) */
            if (Terminal.currentIndex - 1 >= 0) {
                Terminal.Input[Terminal.currentIndex] = 0; 
                Terminal.currentIndex -= 1;
            }

            Terminal.currentX -= (Terminal.zoom * 8);

            /*if (Terminal.currentX + (Terminal.zoom * 8) >= width)  {
                Terminal.currentX = 0;
            }
            else if ((Terminal.currentX - 8 * Terminal.zoom) <= 0){
                Terminal.currentX = width;
                Terminal.currentY += (8 * Terminal.zoom);
            }*/


            /* Draw logic */
            drawChar(' ', Terminal.currentX, Terminal.currentY, 2, Terminal.zoom);
        }
        else if (ch != 0){
            drawChar(ch, Terminal.currentX, Terminal.currentY, 2, Terminal.zoom);
            Terminal.Input[Terminal.currentIndex] = ch;
            Terminal.currentIndex++;

            Terminal.currentX += (Terminal.zoom * 8);
            if((Terminal.currentX + 8 * Terminal.zoom) > width){
                Terminal.currentX = 0;
                Terminal.currentY += (8 * Terminal.zoom);
            }
        }
        else if ((Terminal.currentX + Terminal.zoom*8) >= width && (Terminal.currentY + Terminal.zoom * 8) < height)
        {
            Terminal.currentX = 0;
            Terminal.currentY += (Terminal.zoom * 8);
        }
        else if ((Terminal.currentY + Terminal.zoom*8) >= height && (Terminal.currentX + Terminal.zoom * 8) < width)
        {
            Terminal.currentY = 0;
            Terminal.currentX += (Terminal.zoom * 8);
        }
        else{
            ;
        }
    }
    }

    drawRect(1600, 16, width, 32, 0, 16);

    if (Terminal.currentIndex < 20){
        drawString(1600, 16, (char *) Terminal.Input, 5, 2);
    }
    else{
        for (int i = 0; i < 20; i++){
            drawChar(Terminal.Input[i], (1600 + (16 * i)), 16, 5, 2);
        }
    }

    check_command(Terminal.Input);
    uart_clear_Terminal_Queue();
}

void uart_read_Terminal_Input(unsigned char* buffer){

    for (int i = 0; i < Terminal.currentIndex;i++){
        buffer[i] = Terminal.Input[i];

    }
    buffer[255] = '\0';
}

void uart_write_newLine_to_Terminal(){
    Terminal.currentX = 0;
    Terminal.currentY += (8 * Terminal.zoom);
}

void uart_write_to_Terminal(unsigned char* s, unsigned char attr){
    int rainbow_mode = 0;
    if (attr == RAINBOW_MODE){
        rainbow_mode = 1;
        attr = 0;
    }
    else{
        rainbow_mode = 0;
    }

    while (*s)
    {
        if(*s == '\n' || *s == '\r'){
            Terminal.currentX = 0;
            Terminal.currentY += (8 * Terminal.zoom);
        }
        else if(Terminal.currentX + (8 * Terminal.zoom) > 1920){
            Terminal.currentX = 0;
            Terminal.currentY += (8 * Terminal.zoom);
        }
        else{
            Terminal.currentX += (8 * Terminal.zoom);
        }


        // Do we want some beautiful colors?
        if (rainbow_mode == 1 && attr == 8){
            attr = 1;
        }
        else if (rainbow_mode == 1 && *s != ' '){
            attr++;
        }
        
        drawChar(*s, Terminal.currentX, Terminal.currentY, attr, Terminal.zoom);
        s++;
    }
}

unsigned char getUart()
{
    unsigned char ch = 0;

    if (uart_isReadByteReady()) ch = uart_readByte();
    return ch;
}
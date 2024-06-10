#define PERIPHERAL_BASE 0xFE000000
#define SAFE_ADDRESS    0x00210000 // Somewhere safe to store a lot of data

void uart_init();
void uart_writeText(char *buffer);
void uart_loadOutputFifo();
unsigned char uart_readByte();
unsigned int uart_isReadByteReady();
void uart_writeByteBlocking(unsigned char ch);
void uart_update();
void mmio_write(long reg, unsigned int val);
unsigned int mmio_read(long reg);
void uart_clear_Terminal_Queue();
void uart_reset_Terminal();
// extern unsigned char TerminalInput[256];
// unsigned int findHighestIndex(unsigned char* array, unsigned int size);
// void updateTerminalInput(int x, int y, unsigned char attr, int zoom);
void init_uart_Terminal(int width, int height);
void uart_update_Terminal(int width, int height);
void uart_read_Terminal_Input(unsigned char *buffer);
unsigned char getUart();

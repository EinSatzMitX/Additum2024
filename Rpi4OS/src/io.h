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
extern unsigned char TerminalInput[256];
unsigned int findHighestIndex(unsigned char* array, unsigned int size);
void updateTerminalInput(int x, int y, unsigned char attr, int zoom);
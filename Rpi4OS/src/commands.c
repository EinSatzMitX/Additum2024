#include "../include/io.h"
#include "../include/commands.h"
#include "../include/util.h"
#include "../include/fb.h"

typedef struct Command
{
    unsigned char Command[256];
} Command;

// Define the Commands array at the global scope
Command Commands[10];

void init_Commands(){

   strcpy_custom(Commands[0].Command, "clear");
}

void check_command(unsigned char *command){

   trim_string_at_space(command);
   if (compareStrings(command, Commands[0].Command) == 0)
   {
      drawRect(0, 0, 1920, 1080, 0x00, 1);
   }
   else
   {
      drawChar(compareStrings(command, Commands[0].Command), 100, 100, 5, 3);
   }
}

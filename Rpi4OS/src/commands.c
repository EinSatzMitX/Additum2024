#include "../include/io.h"
#include "../include/commands.h"
#include "../include/util.h"
#include "../include/fb.h"
#include "../include/breakout.h"

typedef struct Command
{
   char Command[256];
} Command;

// Define the Commands array at the global scope
Command Commands[10];

void init_Commands(){
   strcpy_custom(Commands[0].Command, "clear\0");
   strcpy_custom(Commands[1].Command, "breakout\0");
}

void cmd_clear(){
      drawRect(0, 0, 1920, 1080, 0x00, 1);
      uart_reset_Terminal();
}

void cmd_breakout(){
   initBreakout();
}

void check_command(unsigned char *command){

   trim_string_at_newLine(command);
   //
   // CLEAR
   //
   if (compareStrings(command, Commands[0].Command) == 0)
   {
      drawString(1600, 0, "Command found!" , 5, 1);
      cmd_clear();
   }
   //
   // BREAKOUT
   //
   else if(compareStrings(command, Commands[1].Command) == 0){
      cmd_clear();
      initBreakout();
   }
   //
   // No valid Command
   //
   else
   {
      drawString(1600, 0, "Unknown Command:" , 4, 2);
   }
}

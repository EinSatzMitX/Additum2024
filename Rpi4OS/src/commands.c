#include "../include/io.h"
#include "../include/commands.h"
#include "../include/util.h"
#include "../include/fb.h"
#include "../include/breakout.h"
//#include "../include/snake.h"

typedef struct Command
{
   char Command[256];
   char cmd_info[256];
} Command;

// Define the Commands array at the global scope
#define MAX_CMDS 10
int NUM_CMDS = 0;
Command Commands[MAX_CMDS];
Command Secret_Commands[MAX_CMDS];

void init_Commands(){
   strcpy_custom(Commands[0].Command, "clear\0");  strcpy_custom(Commands[0].cmd_info, "Clear the screen with a (not so fancy) animation\0");   NUM_CMDS++;
   strcpy_custom(Commands[1].Command, "breakout\0");  strcpy_custom(Commands[1].cmd_info, "Starts the famous breakout game, inspired by Steve Wozniak\0");   NUM_CMDS++;
   strcpy_custom(Commands[2].Command, "help\0");   strcpy_custom(Commands[2].cmd_info, "you just typed this duuhh\0");    NUM_CMDS++;
   strcpy_custom(Commands[3].Command, "die\0"); strcpy_custom(Commands[3].cmd_info, "hangs this CPU core in an infinte loop (be aware, we're only using one!)\0");    NUM_CMDS++;
   strcpy_custom(Commands[4].Command, "hi\0"); strcpy_custom(Commands[4].cmd_info, "Shows you the Welcome screen again\0");    NUM_CMDS++;
   //strcpy_custom(Commands[5].Command, "snake\0"); strcpy_custom(Commands[5].cmd_info, "Starts the famous snake game\0");    NUM_CMDS++;
   //strcpy_custom(Commands[6].Command, "print\0"); strcpy_custom(Commands[6].cmd_info, "prints a string to the screen. Example: print(100,200,2,2,Hello world!)  this will print Hello World! to x:100, y:200 with the color green and a zoom of 2");   NUM_CMDS++;


   /* Secret Commands */
   strcpy_custom(Secret_Commands[0].Command, "penis\0"); strcpy_custom(Secret_Commands[0].cmd_info, "This is a secret...\0");
}

void cmd_clear(){
      drawRect(0, 0, 1920, 1080, 0x00, 1);
      uart_reset_Terminal();
}

void cmd_breakout(){
   initBreakout();
}

void cmd_help(){
   uart_write_to_Terminal((unsigned char*)"List of Commands:", 2);
   uart_write_newLine_to_Terminal();
   for (int i = 0; i < NUM_CMDS; i++)
   {
      uart_write_to_Terminal((unsigned char *)Commands[i].Command, 2);
      uart_write_to_Terminal((unsigned char *)" - ", 2);
      uart_write_to_Terminal((unsigned char *)Commands[i].cmd_info, 2);
      uart_write_newLine_to_Terminal();
   }
}

void cmd_die(){
   while(1);
}

void cmd_hi(){
   drawRect(0, 0, 1920, 1080, 0, 1);
   uart_reset_Terminal();

   // I don't think I'll have to explain what this does :)
   uart_write_to_Terminal((unsigned char *)"@@@@@@@@                                                                @@@@@@@@", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"@@@@@                                                                      @@@@@", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"@@@                                                                          @@@", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"@@                                                                            @@", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"@                                                                              @", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                                                                                ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                                                                                ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                                                                                ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                      @=@@@@@@@@@@            @@@@@@@@@@=@                      ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                  :@@@-@@----@-@#@@@@@    @@@@@#@-@----@@-@@@:                  ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                  @@----------------@@@  @@@----------------@@                  ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                  @@@----#-----------#@@@@#-----------#----@@@                  ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                  @@&-------@---------@@@@---------@-------&@@                  ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                  @@@----------@------@@@@------@----------@@@                  ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                   @@@-----------@@---@@@@---@@-----------@@@                   ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                    @@@@-----------@@@@@@@@@@-----------@@@@                    ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                     @@@@----------@@@@@@@@@@----------@@@@                     ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                       @@@@------=@@@@@@@@@@@@=------@@@@                       ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                       @@@@------=@@@@@@@@@@@@=------@@@@                       ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                          @@@@@@@@@@@@@##@@@@@@@@@@@@@                          ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                       &@@@@#####@@##########@@#####@@@@%                       ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                      @@@#######@@############@@#######@@@                      ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                     @@@######@@@@############@@@@######@@@                     ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                     @@#####%@@@@@@@########@@@@@@@%#####@@                     ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                    @@@###@@@@@@##@@@@@@@@@@@@##@@@@@@###@@@                    ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                    @@@###@@@@@@##@@@@@@@@@@@@##@@@@@@###@@@                    ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                    @@@#@@@@#########@@@@@@#########@@@@#@@@                    ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                   @@@@@@@@###########@@@@###########@@@@@@@@                   ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                 @@@###@@@############@@@@############@@@###@@@                 ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                @@@####@@@############@@@@############@@@####@@@                ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                @@@####@@@############@@@@############@@@####@@@                ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                @@#####@@@###########@@@@@@###########@@@#####@@                ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                @@#####@@@##########@@@@@@@@##########@@@#####@@                ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                @@@###@@@@@@######@@@@####@@@@######@@@@@@###@@@                ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                 @@@##@@@@@@@@@@@@@##########@@@@@@@@@@@@@##@@@                 ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                  @@@@@###@@@@@@@@#############@@@@@@@###@@@@@                  ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                  @@@@######@@@@@##############@@@@@######@@@@                  ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                   @@@########@@@##############@@@########@@@                   ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                   @@@#########@@##############@@#########@@@                   ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                    @@@########@@@############@@@########@@@                    ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                    :@@@########@@@@########%@@@########@@@,                    ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                     %@@@#######@@@@@@@@@@@@@@@@#######@@@%                     ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                       @@@@####@@@@@@@@@@@@@@@@@@####@@@@                       ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                          @@@@@@@@#############@@@@@@@                          ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                            @@@@@&############@@@@@@                            ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                                @@@##########@@@                                ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"                                  @@@@@@@@@@@@                                  ", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"@                                    @@@@@@                                    @", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"@@                                                                            @@", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"@@@                                                                          @@@", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"@@@@@                                                                      @@@@@", 2);
   uart_write_newLine_to_Terminal();
   uart_write_to_Terminal((unsigned char *)"@@@@@@@@                                                                @@@@@@@@", 2);
   uart_write_newLine_to_Terminal();

   uart_write_to_Terminal((unsigned char *)"Welcome to Oxygen OS!", RAINBOW_MODE);
   uart_write_newLine_to_Terminal();
}

/*
void cmd_snake(){
   cmd_clear();
   init_snake();
}
*/
/*
void cmd_print(int x, int y, unsigned char attr, int zoom, char * s){

   drawString(x, y, (unsigned char *)s, attr, zoom);
   uart_write_newLine_to_Terminal();
}
*/

void cmd_SECRET_penis(){
   cmd_clear();

   uart_write_to_Terminal((unsigned char *)"Wooow you unlocked a secret command!", 7);
   uart_write_newLine_to_Terminal();


   uart_write_to_Terminal((unsigned char *)"8========D", RAINBOW_MODE);
   uart_write_newLine_to_Terminal();
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
   // HELP
   //
   else if(compareStrings(command, Commands[2].Command) == 0){
      cmd_help();
   }
   //
   // DIE
   //
   else if (compareStrings(command, Commands[3].Command) == 0){
      cmd_die();
   }
   //
   // HI
   //
   else if (compareStrings(command, Commands[4].Command) == 0){
      cmd_hi();
   }
   //
   // SNAKE
   //
   else if(compareStrings(command, Commands[5].Command) == 0){
      //cmd_snake();
   }
   //
   // PRINT
   //
   else if(compareStrings(command, Commands[5].Command) == 0){

   }
   //
   // SECRET COMMAND
   // PENIS
   //
   else if(compareStrings(command, Secret_Commands[0].Command) == 0){
      cmd_SECRET_penis();
   }
   //
   // No valid Command
   //
   else
   {
      drawString(1600, 0, "Unknown Command:" , 4, 2);
   }
}

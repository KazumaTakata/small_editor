#ifndef HTERM
#define HTERM


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

typedef enum  {
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
} color8;
void term_goto(int x, int y) { printf("\033[%d;%dH", (y), (x)); }
void term_clear() { printf("\033[2J"); }


// set text color and background color 
// http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html#background-colors
void term_setColor(color8 color) {
  int color_code = 30 + color;
  printf("\033[%dm", color_code);
}
void term_resetColor(){
    printf("\033[0m");
}

void term_setBackColor(color8 color){
  int color_code = 40 + color;
  printf("\033[%dm", color_code); 
}

#endif

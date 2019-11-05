#ifndef HTERM
#define HTERM

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

typedef enum {
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
} color8;

typedef enum {
  UP,
  DOWN,
  RIGHT,
  LEFT,
} ARROW;

typedef struct Cursor {
  int x;
  int y;
} Cursor;

struct winsize getTermSize() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w;
}


int get_cursor_offset (Cursor cursor){
    struct winsize win = getTermSize();     
    return win.ws_col * ( cursor.y - 1 ) + cursor.x;
}

void term_goto(int x, int y) {
  printf("\033[%d;%dH", (y), (x));
  fflush(stdout);
}
void term_clear() {
  printf("\033[2J");
  fflush(stdout);
}

// set text color and background color
// http://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html#background-colors
void term_setColor(color8 color) {
  int color_code = 30 + color;
  printf("\033[%dm", color_code);
  fflush(stdout);
}
void term_resetColor() {
  printf("\033[0m");
  fflush(stdout);
}

void move_cursor(char arrow, Cursor *cur_cursor) {
  printf("\033[%c", arrow);
  fflush(stdout);
  switch (arrow) {
  case 'A':
    if (cur_cursor->y > 1) {
      cur_cursor->y -= 1;
    }
    break;
  case 'B':
    cur_cursor->y += 1;
    break;
  case 'C':
    cur_cursor->x += 1;
    break;
  case 'D':
    if (cur_cursor->x > 1) {
      cur_cursor->x -= 1;
    }
    break;
  }
}

void term_setBackColor(color8 color) {
  int color_code = 40 + color;
  printf("\033[%dm", color_code);
  fflush(stdout);
}

#endif

#include "./raw_mode.h"
#include "./term.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

struct winsize getTermSize() {
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  return w;
}

int main() {
  int i = 0;
  term_clear();
  term_goto(20, 20);
  term_setColor(RED);
  enableRawMode();
  printf("hello boys");
  struct winsize w = getTermSize();
  printf("window size is %d,", w.ws_row);
  printf("window size is %d,", w.ws_col);
  fflush(stdout);
  term_resetColor();
  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    if (iscntrl(c)) {
      printf("%d", c);
      fflush(stdout);
    } else {
      printf("%d ('%c')", c, c);
      fflush(stdout);
    }
  }
}

#include "./process.h"
#include "./raw_mode.h"
#include "./term.h"
#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>




int main(int argc, char *argv[]) {
  char *filename = argv[1];
  char *cur_buffer = NULL;
  FILE *fp = fopen(filename, "r");
  Cursor cur_cursor = {1 , 1};
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  cur_buffer = malloc(size);
  fread(cur_buffer, 1, size, fp);

  int i = 0;
  term_clear();
  term_goto(cur_cursor.x, cur_cursor.y);
  enableRawMode();
  printf("%s", cur_buffer);
  term_goto(cur_cursor.x, cur_cursor.y);

  char c;
  while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
    if (iscntrl(c)) {
      if (c == '\033') {
        read(STDIN_FILENO, &c, 1);
        if (c == '[') {
          read(STDIN_FILENO, &c, 1);
          move_cursor(c, &cur_cursor);
        }
      } else {
        if (c == 127) {
          process_backspace(cur_buffer, &cur_cursor);
          fflush(stdout);
        } else {
          printf("%d", c);
          fflush(stdout);
        }
      }
    } else {
      printf("%d ('%c')", c, c);
      fflush(stdout);
    }
  }
  post_process();
}

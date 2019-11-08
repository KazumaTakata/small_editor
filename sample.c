#include "./process.h"
#include "./raw_mode.h"
#include "./term.h"
#include <ctype.h>

#include "./buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

Line_contents split_by_newline(char *content, int size) {
  int start_id = 0;
  int counter = 0;
  int line_id = 0;
  Line_buffer **line_contents = malloc(1000);

  for (int i = 0; i < size; i++) {
    counter++;
    if (content[i] == '\n') {
      char *line_content = malloc(counter);
      for (int j = 0; j < counter - 1; j++) {
        line_content[j] = content[j + start_id];
      }

      Line_buffer *line_buffer = malloc(sizeof(Line_buffer));
      line_buffer->content = line_content;
      line_buffer->cap = counter;
      line_buffer->size = counter;

      line_contents[line_id] = line_buffer;

      start_id += counter;
      counter = 0;
      line_id++;
    }
  }
  Line_contents lc = {line_contents, line_id};

  return lc;
}

int main(int argc, char *argv[]) {
  char *filename = argv[1];
  char *cur_buffer = NULL;
  FILE *fp = fopen(filename, "r");
  Cursor cur_cursor = {1, 1};
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  cur_buffer = malloc(size);
  fread(cur_buffer, 1, size, fp);

  Line_contents line_contents = split_by_newline(cur_buffer, size);

  //  Content_buffer buffer = {cur_buffer , size, size };
  int i = 0;
  term_clear();
  term_goto(cur_cursor.x, cur_cursor.y);
  enableRawMode();
  print_lines(line_contents);
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
          //backspace
          process_backspace(line_contents, &cur_cursor);
          fflush(stdout);
        } else if (c == 13) {
          // enter key
          process_enterkey(line_contents, &cur_cursor);
        } else {
          printf("%d", c);
          fflush(stdout);
        }
      }
    } else {
      process_insert(line_contents, &cur_cursor, c);
      // printf("%d ('%c')", c, c);
      // fflush(stdout);
    }
  }
  post_process();
}

#ifndef HBUFFER
#define HBUFFER

#include "term.h"



typedef struct Line_buffer {
  char *content;
  int cap;
  int size;
} Line_buffer;

typedef struct Line_contents {
  Line_buffer **line_buffer;
  int size;

} Line_contents;

void print_lines(Line_contents line_contents) {

  int size = line_contents.size;

  for (int i = 0; i < size; i++) {
    printf("%s", line_contents.line_buffer[i]->content);
    fflush(stdout);
  }
}
void enlarge_buffer() {}

void insert_buffer() {}

void delete_one_buffer(Line_contents buffer, int pos) {
  for (int i = pos; i < buffer.size; i++) {
   // buffer->content[i] = buffer->content[i + 1];
  }
  //buffer->size -= 1;
}

void update_display(Line_contents buffer, Cursor *cursor) {
  term_clear();
  term_goto(1, 1);
  print_lines( buffer);
  fflush(stdout);
  term_goto(cursor->x, cursor->y);
}

#endif

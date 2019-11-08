#ifndef HBUFFER
#define HBUFFER

typedef struct Line_buffer {
  char *content;
  int cap;
  int size;
} Line_buffer;

typedef struct Line_contents Line_contents;

struct Line_contents {
  Line_buffer **line_buffer;
  int size;
};

#include "term.h"
void print_lines(Line_contents *line_contents) {

  int size = line_contents->size;

  for (int i = 0; i < size; i++) {
    printf("%s\n", line_contents->line_buffer[i]->content);
    fflush(stdout);
  }
}
void enlarge_buffer() {}

void insert_buffer() {}

void insert_one_buffer(Line_contents *buffer, int offset_x, int offset_y,
                       char ch) {

  offset_y += -1;

  if (buffer->line_buffer[offset_y]->size >=
      buffer->line_buffer[offset_y]->cap) {
    char *newcontent = calloc(2 * buffer->line_buffer[offset_y]->cap, sizeof(char) );
    for (int i = 0; i < buffer->line_buffer[offset_y]->size; i++) {
      newcontent[i] = buffer->line_buffer[offset_y]->content[i];
    }
    free(buffer->line_buffer[offset_y]->content);
    buffer->line_buffer[offset_y]->content = newcontent;
    buffer->line_buffer[offset_y]->cap = 2 * buffer->line_buffer[offset_y]->cap;
  }

  for (int i = buffer->line_buffer[offset_y]->size; i >= offset_x -1 ; i--) {
    buffer->line_buffer[offset_y]->content[i + 1] =
        buffer->line_buffer[offset_y]->content[i];
  }
  buffer->line_buffer[offset_y]->content[offset_x - 1] = ch;
  buffer->line_buffer[offset_y]->size += 1;
}

void delete_one_buffer(Line_contents *buffer, int offset_x, int offset_y) {

  offset_y += -1;

  for (int i = offset_x - 2; i < buffer->line_buffer[offset_y]->size; i++) {
    buffer->line_buffer[offset_y]->content[i] =
        buffer->line_buffer[offset_y]->content[i + 1];
  }
  buffer->line_buffer[offset_y]->size -= 1;
}

void update_display(Line_contents *buffer, Cursor *cursor) {
  term_clear();
  term_goto(1, 1);
  print_lines(buffer);
  fflush(stdout);
  term_goto(cursor->x, cursor->y);
}

#endif

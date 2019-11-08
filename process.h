#ifndef HPROCESS
#define HPROCESS

#include "./buffer.h"
#include "./term.h"

void post_process() { term_clear(); }

// int get_cursor_offset(Line_contents buffer, Cursor *cur_cursor) {
// struct winsize win = getTermSize();
// int offset = 0;
// for (int i = 0; i < (cursor.y - 1); i++) {
// offset += buffer.line_buffer[i]->size;
//}
// return offset + cursor.x;
/*}*/

void process_backspace(Line_contents *buffer, Cursor *cur_cursor) {

  if (cur_cursor->x > 1) {
    delete_one_buffer(buffer, cur_cursor->x, cur_cursor->y);
    cur_cursor->x -= 1;

    term_goto(cur_cursor->x, cur_cursor->y);
    update_display(buffer, cur_cursor);
  }
}

void process_enterkey(Line_contents *buffer, Cursor *cur_cursor) {
  int offset_y = cur_cursor->y - 1;
  int offset_x = cur_cursor->x - 1;

  int newline_size = buffer->line_buffer[offset_y]->size - offset_x;
  int cap;

  char *newline;
  if (newline_size <= 0) {
    cap = 2;
    newline = calloc(2, sizeof(char) );
  } else {
    cap = newline_size * 2;
    newline = calloc(newline_size * 2 + 1, sizeof(char)  ) ;
  }
  for (int i = 0; i < newline_size; i++) {
    newline[i] = buffer->line_buffer[offset_y]->content[offset_x + i];
    buffer->line_buffer[offset_y]->content[offset_x + i] = 0x00;
  }

  buffer->line_buffer[offset_y]->size = offset_x;

  for (int i = buffer->size; i > offset_y; i--) {
    buffer->line_buffer[i + 1] = buffer->line_buffer[i];
  }
  buffer->size += 1;
  Line_buffer *newlinebuffer = malloc(sizeof(Line_buffer));
  newlinebuffer->content = newline;
  newlinebuffer->size = newline_size;
  newlinebuffer->cap = cap;
  buffer->line_buffer[offset_y + 1] = newlinebuffer;

  update_display(buffer, cur_cursor);
  cur_cursor->x = 1;
  cur_cursor->y = cur_cursor->y + 1;
  term_goto(cur_cursor->x, cur_cursor->y);
}

void process_insert(Line_contents *buffer, Cursor *cur_cursor, char ch) {
  insert_one_buffer(buffer, cur_cursor->x, cur_cursor->y, ch);
  cur_cursor->x += 1;
  term_goto(cur_cursor->x, cur_cursor->y);
  update_display(buffer, cur_cursor);
}
#endif

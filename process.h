#include "./term.h"

void post_process() { term_clear(); }

void process_backspace(char *cur_buffer, Cursor *cur_cursor) {
  if (cur_cursor->x > 1) {
    cur_cursor->x -= 1;
  }
  int offset = get_cursor_offset(*cur_cursor);


  term_goto(cur_cursor->x, cur_cursor->y);
}

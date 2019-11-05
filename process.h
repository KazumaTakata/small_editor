#ifndef HPROCESS
#define HPROCESS

#include "./buffer.h"
#include "./term.h"

void post_process() { term_clear(); }

void process_backspace(Line_contents buffer, Cursor *cur_cursor) {
  if (cur_cursor->x > 1) {
    cur_cursor->x -= 1;
  }
  int offset = get_cursor_offset(*cur_cursor);

  term_goto(cur_cursor->x, cur_cursor->y);

  //delete_one_buffer(buffer, offset);

  update_display(buffer, cur_cursor );    

}

#endif

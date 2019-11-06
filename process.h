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

void process_backspace(Line_contents buffer, Cursor *cur_cursor) {

  if (cur_cursor->x > 1) {
    delete_one_buffer(buffer, cur_cursor->x, cur_cursor->y);
    cur_cursor->x -= 1;

    term_goto(cur_cursor->x, cur_cursor->y);
    update_display(buffer, cur_cursor);
  }
}

void process_insert(Line_contents buffer, Cursor *cur_cursor, char ch) {

  insert_one_buffer(buffer, cur_cursor->x, cur_cursor->y, ch );
  cur_cursor->x += 1;
  term_goto(cur_cursor->x, cur_cursor->y);
  update_display(buffer, cur_cursor);
}

#endif

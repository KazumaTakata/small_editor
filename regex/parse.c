#include "parse.h"
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void test2() {
  char *data = "abbee";

  Regex_data regex_data = {data, 0};

  Regex *regex = parseRegex(&regex_data);

  assert(regex->term->factors[0]->base->ch == 'a');
  assert(regex->term->factors[1]->base->ch == 'b');
  assert(regex->term->factors[2]->base->ch == 'b');
  assert(regex->term->factors[3]->base->ch == 'e');
  assert(regex->term->factors[4]->base->ch == 'e');
  assert(regex->term->size == 5 );
}

void test() {
  char *data = "a*|b";

  Regex_data regex_data = {data, 0};

  Regex *regex = parseRegex(&regex_data);

  assert(regex->term->factors[0]->base->ch == 'a');
  assert(regex->term->factors[0]->quan == ASTARISK);
  assert(regex->next->term->factors[0]->base->ch == 'b');
}

int main() { test2(); }

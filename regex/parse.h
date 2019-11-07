#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

typedef enum Quantification {
  ASTARISK,
  PLUS,
  QUESTION,
  SINGLE,
} Quantification;

typedef struct Base {
  char ch;
} Base;

typedef struct Factor {
  Base *base;
  Quantification quan;

} Factor;

typedef struct Term {
  Factor **factors;
  int size;
} Term;

typedef struct Regex {
  Term *term;
  struct Regex *next;
} Regex;

typedef struct Regex_data {
  char *data;
  int pos;
} Regex_data;

Base *parseBase(Regex_data *data) {
  Base *base = malloc(sizeof(Base));
  base->ch = data->data[data->pos];

  data->pos++;

  return base;
}

Factor *parseFactor(Regex_data *data) {

  Factor *factor = malloc(sizeof(Factor));

  Base *base = parseBase(data);

  factor->base = base;

  if (data->data[data->pos] == '*') {
    factor->quan = ASTARISK;
    data->pos++;
  }else {
    factor->quan = SINGLE; 
  }

  return factor;
}

char getCurChar(Regex_data *data) {
  int leng = strlen(data->data);
  if (leng > data->pos) {
    return data->data[data->pos];
  }

  return 0;
}

Term *parseTerm(Regex_data *data) {

  Term *term = malloc(sizeof(Term));
  Factor **factor_list = malloc(sizeof(Factor *) * 100);

  int i = 0;
  while (isalpha(getCurChar(data))) {

    Factor *factor = parseFactor(data);
    factor_list[i] = factor;
    i++;
  }

  term->factors = factor_list;
  term->size = i;

  return term;
}

Regex *parseRegex(Regex_data *data) {

  Regex *regex = malloc(sizeof(Regex));
  Term *term = parseTerm(data);
  regex->term = term;

  if (getCurChar(data) == '|') {
    data->pos++;
    Regex *regex2 = parseRegex(data);
    regex->next = regex2;
  }

  return regex;
}


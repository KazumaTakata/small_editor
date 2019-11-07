#include <stdio.h>
#include <stdlib.h>

typedef struct Edge Edge;
typedef struct Node Node;

typedef struct Edge {
  char ch;
  Node *next;
} Edge;

typedef struct Node {
  Edge *edge1;
  Edge *edge2;
  int size;

} Node;

typedef struct Frag {
  Node *start;
  Edge **outEdge;
  int size;
} Frag;

Frag GenConcatFrag(Frag frag1, Frag frag2) {

  for (int i = 0; i < frag1.size; i++) {
    frag1.outEdge[i]->next = frag2.start;
  }
  Frag frag = {frag1.start, frag2.outEdge, frag2.size};

  return frag;
}

Frag GenAlternationFrag(Frag frag1, Frag frag2) {
  Node *node = malloc(sizeof(Node));
  node->size = 2;

  Edge *edge1 = malloc(sizeof(Edge));
  edge1->ch = 0;
  edge1->next = frag1.start;

  Edge *edge2 = malloc(sizeof(Edge));
  edge2->ch = 0;
  edge2->next = frag2.start;

  node->edge1 = edge1;
  node->edge2 = edge2;

  Edge **out = malloc(sizeof(Edge **) * (frag1.size + frag2.size));
  for (int i = 0; i < frag1.size; i++) {
    out[i] = frag1.outEdge[i];
  }
  for (int i = 0; i < frag2.size; i++) {
    out[i + frag1.size] = frag2.outEdge[i];
  }

  Frag frag = {node, out, frag2.size + frag1.size};

  return frag;
}

Frag GenLiteralFrag(char ch) {

  Node *node = malloc(sizeof(Node));
  node->size = 1;

  Edge *edge = malloc(sizeof(Edge));
  edge->ch = ch;
  edge->next = NULL;

  node->edge1 = edge;
  Edge **out = malloc(sizeof(Edge **));
  out[0] = edge;
  Frag frag = {node, out, 1};

  return frag;
}

Frag constructNFA2(char *regex) {
  Frag frag1 = GenLiteralFrag('a');
  Frag frag2 = GenLiteralFrag('b');

  Frag frag3 = GenAlternationFrag(frag1, frag2);

  return frag3;
}
Frag constructNFA(char *regex) {
  Frag frag1 = GenLiteralFrag(regex[0]);
  Frag frag2 = GenLiteralFrag(regex[1]);
  Frag frag3 = GenLiteralFrag(regex[2]);

  Frag frag4 = GenConcatFrag(frag1, frag2);
  Frag frag5 = GenConcatFrag(frag4, frag3);

  return frag5;
}

void test2(Frag ff) {
  if (ff.start->size != 2) {
    printf("error");
  }

  if (ff.start->edge1->ch != 0) {
    printf("error");
  }

  Node *next = ff.start->edge1->next;

  if (next->size != 1) {
    printf("error");
  }

  if (next->edge1->ch != 'a') {
    printf("error");
  }
  Node *next2 = ff.start->edge2->next;

  if (next2->size != 1) {
    printf("error");
  }

  if (next2->edge1->ch != 'b') {
    printf("error");
  }
}

void test(Frag ff) {
  if (ff.start->size != 1) {
    printf("error");
  }

  if (ff.start->edge1->ch != 'a') {
    printf("error");
  }

  Node *next = ff.start->edge1->next;

  if (next->size != 1) {
    printf("error");
  }

  if (next->edge1->ch != 'b') {
    printf("error");
  }

  Node *next1 = next->edge1->next;

  if (next1->edge1->ch != 'b') {
    printf("error");
  }
  if (next1->edge1->next != NULL) {
    printf("error");
  }
}




int main() {

  /*char *regex_code = "abb";*/
  /*Frag ff = constructNFA(regex_code);*/
  /*test(ff);*/

  char *regex_code = "a|b";
  Frag ff = constructNFA2(regex_code);
  test2(ff);
}
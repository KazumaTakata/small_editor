#include "regex.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test4() {

  char *regex_code = "abb";
  Frag ff = constructNFA(regex_code);

  bool ifmatched = match(ff, regex_code);

  assert(ifmatched == true);
}
void test5() {

  char *regex_code = "abb";
  Frag ff = constructNFA(regex_code);

  bool ifmatched = match(ff, "ac");

  assert(ifmatched == false);
}

void test6() {

  char *regex_code = "abbaeed";
  Frag ff = constructNFA3(regex_code);

  bool ifmatched = match(ff, "abbaeed");

  assert(ifmatched == true);
}

void test7() {

  char *regex_code = "abbee";
  Frag ff = constructNFA3(regex_code);

  bool ifmatched = match(ff, "abbee");

  assert(ifmatched== true);
}

void test3() {

  char *regex_code = "abb";
  Frag ff = constructNFA(regex_code);

  NodeList nodelist1 = {&ff.start, 1};

  NodeList nodelist2 = step(nodelist1, 'a');

  assert(nodelist2.nodes[0]->edge1->ch == 'b');

  assert(nodelist2.size == 1);

  NodeList nodelist3 = step(nodelist2, 'b');

  assert(nodelist3.nodes[0]->edge1->ch == 'b');

  assert(nodelist3.size == 1);

  NodeList nodelist5 = step(nodelist3, 'b');

  assert(nodelist5.nodes[0]->size == 0);

  bool ifcontain = ifContainGoal(nodelist5);

  assert(ifcontain == true);

  NodeList nodelist4 = step(nodelist2, 'c');
  assert(nodelist4.size == 0);
}
void test2() {

  char *regex_code = "a|b";
  Frag ff = constructNFA2(regex_code);

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

void test() {

  char *regex_code = "abb";
  Frag ff = constructNFA(regex_code);

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

  /*  test();*/
  /*test2();*/

  test3();
  test4();
  test5();
  test6();
  test7();
}

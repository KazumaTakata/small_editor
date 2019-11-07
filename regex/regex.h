#ifndef HREGEX
#define HREGEX

#include <assert.h>

#include "parse.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge Edge;
typedef struct Node Node;

typedef struct Edge {
  char ch;
  Node *next;
} Edge;

// if size == 0 : node is goal node
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

typedef struct NodeList {
  Node **nodes;
  int size;
} NodeList;

bool ifContainGoal(NodeList list) {
  if (list.size == 0) {
    return false;
  }

  for (int i = 0; i < list.size; i++) {
    if (list.nodes[i]->size == 0) {
      return true;
    }
  }

  return false;
}

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

Frag GenGoalFrag() {

  Node *node = malloc(sizeof(Node));
  node->size = 0;

  Frag goalFrag = {node, NULL, 0};

  return goalFrag;
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

NodeList step(NodeList state, char ch) {
  Node **nodes = malloc(sizeof(Node *) * 100);
  int numberOfNodes = 0;
  for (int i = 0; i < state.size; i++) {
    if (state.nodes[i]->size == 0) {
      // if state is goal : ignore
    } else if (state.nodes[i]->size == 1) {
      // if node has one edge;
      if (state.nodes[i]->edge1->ch == ch) {
        nodes[numberOfNodes] = state.nodes[i]->edge1->next;
        numberOfNodes++;
      }
    } else {
      // if node has two edge;
      if (state.nodes[i]->edge1->ch == ch) {
        nodes[numberOfNodes] = state.nodes[i]->edge1->next;
        numberOfNodes++;
      }
      if (state.nodes[i]->edge2->ch == ch) {
        nodes[numberOfNodes] = state.nodes[i]->edge2->next;
        numberOfNodes++;
      }
    }
  }
  NodeList nodelist = {nodes, numberOfNodes};

  return nodelist;
}

Frag constructNFA2(char *regex) {
  Frag frag1 = GenLiteralFrag('a');
  Frag frag2 = GenLiteralFrag('b');
  Frag goal = GenGoalFrag();

  Frag frag3 = GenAlternationFrag(frag1, frag2);
  Frag frag4 = GenConcatFrag(frag3, goal);

  return frag4;
}

Frag constructFromBase(Base *base) {
  Frag frag = GenLiteralFrag(base->ch);

  return frag;
}
Frag constructFromFactor(Factor *factor) {
  Frag baseFrag = constructFromBase(factor->base);
  Frag accumFrag;
  if (factor->quan == ASTARISK) {
    //accumFrag = baseFrag;
  } else {
    accumFrag = baseFrag;
  }

  return accumFrag;
}

Frag constructFromTerm(Term *term) {

  Frag accumFrag;

  for (int i = 0; i < term->size; i++) {
    Frag factorFrag = constructFromFactor(term->factors[i]);
    if (i == 0) {
      accumFrag = factorFrag;
    } else {
      accumFrag = GenConcatFrag(accumFrag, factorFrag);
    }
  }

  return accumFrag;
}

Frag constructFromRegex(Regex *regex) {
  Frag termFrag = constructFromTerm(regex->term);

  return termFrag;
}

Frag constructNFA3(char *regex_d) {

  Regex_data regex_data = {regex_d, 0};

  Regex *regex = parseRegex(&regex_data);

  Frag regexFrag = constructFromRegex(regex);

  Frag goal = GenGoalFrag();
  Frag frag = GenConcatFrag(regexFrag, goal);

  return frag;
}

Frag constructNFA(char *regex) {
  Frag frag1 = GenLiteralFrag(regex[0]);
  Frag frag2 = GenLiteralFrag(regex[1]);
  Frag frag3 = GenLiteralFrag(regex[2]);

  Frag frag4 = GenConcatFrag(frag1, frag2);
  Frag frag5 = GenConcatFrag(frag4, frag3);

  Frag goal = GenGoalFrag();
  Frag frag6 = GenConcatFrag(frag5, goal);

  return frag6;
}

bool match(Frag regexFrag, char *target) {

  int leng = strlen(target);

  NodeList nodelist = {&regexFrag.start, 1};

  for (int i = 0; i < leng; i++) {
    nodelist = step(nodelist, target[i]);
  }

  bool ifcontain = ifContainGoal(nodelist);

  return ifcontain;
}

#endif

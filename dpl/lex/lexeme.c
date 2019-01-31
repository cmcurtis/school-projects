//author:  Caley Curtis

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexeme.h"
#include "types.h"

struct Lexeme{
  char *type;
  int ival;
  double rval;
  char *sval;
  char *kval;
};

char* getType(lexeme *l) {
  return l->type;
}

lexeme *newLexeme(char *t){
  lexeme *l = malloc(sizeof(lexeme));
  assert (l != 0);
  
  l->type = t;
  return l;
};

lexeme *newLexemeInt(int x) {
  lexeme *p = malloc(sizeof(lexeme));
  assert(p != 0);
  p->type = type_INT;
  p->ival = x;
  return p;
  }

lexeme *newLexemeReal(double x){
  lexeme *p = malloc(sizeof(lexeme));
  assert(p != 0);
  p->type = type_REAL;
  p->rval = x;
  return p;
}

lexeme *newLexemeChar(char *type, char *x){
  lexeme *p = malloc(sizeof(lexeme));
  assert(p != 0);
  p->type = type;
  p->sval = x;
  return p;
}

lexeme *newLexemeKeyword(char *type, char *x){
  // printf("type: %s, x: %s\n", type, x);
  lexeme *p = malloc(sizeof(lexeme));
  assert(p != 0);
  p->type = type;
  p->kval = x;
  return p;
}
  
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
  int lineNum;
  lexeme *left;
  lexeme *right;
};

/*
accessors
*/
char* getType(lexeme *l) { return l->type; }
int getLineNum(lexeme *l) { return l->lineNum; }

/*
setters
*/
void setLeftLex(lexeme *x, lexeme *l){ x->left = l; }
void setRightLex(lexeme *x, lexeme *r){ x->right = r; }

/*
constructors
*/
lexeme *newLexeme(char *t, int n){
  lexeme *l = malloc(sizeof(lexeme));
  assert (l != 0);
  
  l->type = t;
  l->lineNum = n;
  return l;
}

lexeme *newErrorLexeme(char *err, char *message, int n){
  lexeme *e = malloc(sizeof(lexeme));
  assert (e != 0);

  e->type = err;
  e->lineNum = n;
  printf("%s @ line: %d", message, n);
 
  // exit(1);
  return e;
}


lexeme *newLexemeInt(int x, int n) {
  lexeme *p = malloc(sizeof(lexeme));
  assert(p != 0);
  p->type = type_INT;
  p->ival = x;
  p->lineNum = n;
  return p;
  }

lexeme *newLexemeReal(double x, int n){
  lexeme *p = malloc(sizeof(lexeme));
  assert(p != 0);
  p->type = type_REAL;
  p->rval = x;
  p->lineNum = n;
  return p;
}

lexeme *newLexemeChar(char *type, char *x, int n){
  lexeme *p = malloc(sizeof(lexeme));
  assert(p != 0);
  p->type = type;
  p->sval = x;
  return p;
}

lexeme *newLexemeKeyword(char *type, char *x, int n){
  // printf("type: %s, x: %s\n", type, x);
  lexeme *p = malloc(sizeof(lexeme));
  assert(p != 0);
  p->type = type;
  p->kval = x;
  p->lineNum = n;
  return p;
}
  
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
  lexeme **aval;
  lexeme *(*fval)(lexeme *);
  int lineNum;
  lexeme *left;
  lexeme *right;
};

/*
accessors
*/
char* getType(lexeme *l) { return l->type; }
int getLineNum(lexeme *l) { return l->lineNum; }
char* getSval(lexeme *l) { return l->sval; }
int getIval(lexeme *l) { return l->ival; }
double getRval(lexeme *l) { return l->rval; }
char* getKval(lexeme *l) { return l->kval; }
char* getFval(lexeme *l) { return l->fval; }

/*
helpers
*/
void setType(lexeme *l, char *type){
  l->type = type;
}

lexeme *car(lexeme *x){ return x->left; }
lexeme *cdr(lexeme *x){ return x->right; }
void setCar(lexeme *x, lexeme *y){ x->left = y; }
void setCdr(lexeme *x, lexeme *y){ x->right = y; }

lexeme *cons(char *type, lexeme *left, lexeme *right){
  lexeme *n = newLexeme(type, 0);
  setCar(n, left);
  setCdr(n, right);
  return n;
}

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
  printf("%s @ line: %d\n", message, n);
 
  // exit(1);
  return e;
}

lexeme *newLexemeBool(int x, int n) {
  lexeme *p = malloc(sizeof(lexeme));
  assert(p != 0);
  p->type = type_BOOL;
  p->ival = x;
  p->lineNum = n;
  return p;
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

void displayLexeme(lexeme *x){
  if (x->type == VARIABLE){
    printf("%s", x->kval);
  }
  else if(x->type == type_INT){
    printf("%d", x->ival);
  }
  else if(x->type == type_REAL){
    printf("%f", x->rval);
  }
  else if(x->type == type_STRING){
    printf("%s", x->sval);
  }
}

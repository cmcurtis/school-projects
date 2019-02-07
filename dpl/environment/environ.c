//author: Caley Curtis

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "lexeme.h"
#include "environ.h"

void Fatal(char *,...); 
void displayVars(lexeme *x, lexeme *y);

int sameVar(lexeme *id, lexeme *var) {
  if (strcmp(getSval(id), getSval(var)) == 0) { return 1; }
  else return 0;
}

lexeme *createEnv() {
  return cons("ENV", NULL, cons("TABLE", NULL, NULL));
}

lexeme *lookupVal(lexeme *env, lexeme *id) {
  while (env != NULL)
    {
    lexeme *table = car(env);
    lexeme *vars = car(table);
    lexeme *vals = cdr(table);
    while (vars != NULL)
        {
        if (sameVariable(id,car(vars)))
            {
            return car(vals);
            }
        vars = cdr(vars);
        vals = cdr(vals);
        }
    env = cdr(env);
    }

  // Fatal("variable ", id," is undefined");
  return NULL;
}

lexeme *updateEnv(lexeme *env, lexeme *id, lexeme *val){
  while (env != NULL)
    {
    lexeme *table = car(env);
    lexeme *vars = car(table);
    lexeme *vals = cdr(table);
    while (vars != NULL)
        {
        if (sameVariable(id,car(vars)))
            {
            setCar(id, val);
            return val;
            }
        vars = cdr(vars);
        vals = cdr(vals);
        }
    env = cdr(env);
    }

  // Fatal("variable ", id," is undefined");
  return NULL;
}

lexeme *insertEnv(lexeme *env, lexeme *id, lexeme *val){
  lexeme *table = car(env);
  setCar(table, cons("JOIN", id, car(table)));
  setCdr(table, cons("JOIN", val, cdr(table)));
  return val;
}

lexeme *extendEnv(lexeme *env, lexeme *vars, lexeme *vals){
  return cons("ENV", cons("VALUES", vars, vals), env);
}

void displayEnv(lexeme *env){
  printf("The environment is:\n");
  if (env == NULL) { 
    printf("EMPTY"); 
    return; 
  }

  while(env != NULL) {
    lexeme *table = car(env);
    lexeme *vars = car(table);
    lexeme *vals = cdr(table);
    //display vars & vals
    while(vars != NULL) {
      displayVars(vars, vals);
      vars = cdr(vars);
      vals = cdr(vals);
    }
    env = cdr(env);
  }
}

void displayLocal(lexeme *env) {
  printf("The local environment is:\n");
  if (env == NULL) { printf("EMPTY"); }
  
  lexeme *table = car(env);
  lexeme *vars = car(table);
  lexeme *vals = cdr(table);
  
  while(vars != NULL) {
    //TODO
    displayVars(vars, vals);
    vars = cdr(vars);
    vals = cdr(vals);
  }
}

void displayVars(lexeme *x, lexeme *y){
  printf("\t");
  displayLexeme(x);
  printf(" = ");
  displayLexeme(y);
  printf("\n");
}

//from Lusth
void Fatal(char *fmt, ...) {
  va_list ap;

  fprintf(stderr,"An error occured: ");
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);

  exit(-1);
}
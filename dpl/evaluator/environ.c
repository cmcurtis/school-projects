//author: Caley Curtis

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "lexeme.h"
#include "types.h"
#include "environ.h"

void Fatal(char *,...); 
void displayVars(lexeme *x, lexeme *y);

int sameVar(lexeme *id, lexeme *var);

lexeme *createEnv() {
  // ch 4
  return cons(ENV, cons(TABLE, NULL, NULL), NULL);
}

lexeme *lookupVal(lexeme *env, lexeme *id) {
  //ch 4
  while (env != NULL)
    {
    lexeme *table = car(env);
    lexeme *vars = car(table);
    lexeme *vals = cdr(table);
    while (vars != NULL)
        {
        if (sameVar(id,car(vars)))
            {
            return car(vals);
            }
        vars = cdr(vars);
        vals = cdr(vals);
        }
    env = cdr(env);
    }

  Fatal("variable %s is undefined\n", getKval(id));
  return NULL;
}

lexeme *updateEnv(lexeme *env, lexeme *id, lexeme *val){
  //ch 4
  while (env != NULL)
    {
    lexeme *table = car(env);
    lexeme *vars = car(table);
    lexeme *vals = cdr(table);
    while (vars != NULL)
        {
        if (sameVar(id,car(vars)))
            {
            setCar(vals, val);
            return car(vals);
            }
        vars = cdr(vars);
        vals = cdr(vals);
        }
    env = cdr(env);
    }

  Fatal("variable %s is undefined\n", getKval(id));
  return NULL;
}

lexeme *insertEnv(lexeme *env, lexeme *id, lexeme *val){
  //ch 4
  lexeme *table = car(env);
  setCar(table, cons("JOIN", id, car(table)));
  // printf("CAR is: %s\n", getType(car(table)));
  // printf("CAR's value is: %s", getType(car(car(table))));
  setCdr(table, cons("JOIN", val, cdr(table)));
  // printf("CDR is: %s\n", getType(cdr(table)));
  // printf("CDR's value is: %s", getType(car(cdr(table))));
  return val;
}

lexeme *extendEnv(lexeme *env, lexeme *vars, lexeme *vals){
  // ch 4
  return cons(ENV, cons(TABLE, vars, vals), env);
}

int sameVar(lexeme *id, lexeme *var) {
  if (strcmp(getKval(id), getKval(var)) == 0) { return 1; }
  else return 0;
}

void displayEnv(lexeme *env){
  printf("The environment is:\n");
  int count = 0;
  //ch 4
  if (car(car(env)) == NULL) { 
    printf("EMPTY\n"); 
    return; 
  }

  while(env != NULL) {
    lexeme *table = car(env);
    lexeme *vars = car(table);
    lexeme *vals = cdr(table);
    //display vars & vals
    while(vars != NULL) {
      if (count > 0) {
        printf("\t");
      }
      displayVars(car(vars), car(vals));
      vars = cdr(vars);
      vals = cdr(vals);
    }
    count++;
    env = cdr(env);
  }
}

void displayLocal(lexeme *env) {
  printf("The local environment is:\n");

  //ch4
  if (car(car(env)) == NULL) { printf("EMPTY\n"); }
  
  lexeme *table = car(env);
  lexeme *vars = car(table);
  lexeme *vals = cdr(table);
  
  while(vars != NULL) {
    printf("displaying local");
    displayVars(car(vars), car(vals));
    vars = cdr(vars);
    vals = cdr(vals);
  }
}

void displayVars(lexeme *x, lexeme *y){
  printf("\t%s = ", getKval(x));
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
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexeme.h"
#include "environ.h"

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
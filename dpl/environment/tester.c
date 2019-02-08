//author: Caley Curtis

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "lexeme.h"
#include "types.h"
#include "environ.h"

int main(void){
  lexeme *env = createEnv();
  displayEnv(env);
  insertEnv(env, newLexemeKeyword(VARIABLE, "x", 0), newLexemeInt(10, 0));
  insertEnv(env, newLexemeKeyword(VARIABLE, "y", 0), newLexemeChar(type_STRING, "hello", 0));
  displayEnv(env);
  lexeme *env2 = createEnv();
  insertEnv(env, newLexemeKeyword(VARIABLE, "a", 0), newLexemeInt(6, 0));
  insertEnv(env, newLexemeKeyword(VARIABLE, "b", 0), newLexemeChar(type_STRING, "bye", 0));
  lexeme *temp = extendEnv(env, car(car(env2)), cdr(car(env2)));
  displayLocal(env);
  displayEnv(env);
  printf("Searching for x:\n");
  temp = lookupVal(env, newLexemeKeyword(VARIABLE, "x", 0));
  printf("Found x with value: ");
  displayLexeme(temp);
  printf("\n");

  printf("Updating b:\n");
  temp = updateEnv(env, newLexemeKeyword(VARIABLE, "c", 0), newLexemeChar(type_STRING, "goodbye", 0));
  printf("Found b with value: ");
  displayLexeme(temp);
  printf("\n");
  displayEnv(env);
}
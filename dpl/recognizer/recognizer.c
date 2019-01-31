#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "recognizer.h"

void display(lexeme *l) {
  printf("%s\n", getType(l));
  
}

void scanner(FILE *fileName){ 
  lexeme *token; 
  token = newLexeme("BLANK");

  token = lex(fileName); 
  while (getType(token)) 
      { 
      display(token);
      if (getType(token) == END_OF_FILE) break;
      token = lex(fileName);
      }
  // display(newLexeme(END_OF_FILE));
  }

int main(int argc, char **argv){
  if (argc == 1) {
    printf("%d arguments!\n",argc-1); 
    exit(1);
  }

  FILE *fp;
  fp = fopen(argv[1], "r");
  scanner(fp);
  fclose(fp);
}



lexeme *program(){
  lexeme *d = def();
  if (programPending) program();
  lexeme *e = match(END_OF_FILE);
  return cons("PROGRAM", d, e);
}

lexeme *def() {
  if (classPending()) return classFunc(); 
  else if (varDefPending()) return varDef();
  else if (functionPending()) return function();
}

lexeme *op() {
  if (check(PLUS)) return match(PLUS);
  else if (check(MINUS)) return match(MINUS);
  else if (check(EQUALS)) return match(EQUALS);
  else if (check(TIMES)) return match(TIMES);
  else if (check(DIVIDE)) return match(DIVIDE);
  else if (check(EXPONENT)) return match(EXPONENT);
  else if (check(MODULO)) return match(MODULO);
  else if (check(AND)) return match(AND);
  else if (check(OR)) return match(OR);
  else if (check(EQUALTO)) return match(EQUALTO);
  else if (check(GTHAN)) return match(GTHAN);
  else if (check(LTHAN)) return match(LTHAN);
}

lexeme *unary(){
  if (check(VARIABLE)) return match(VARIABLE);
  else if (check(type_INT)) return match(type_INT);
  else if (check(type_REAL)) return match(type_REAL);
  else if (check(type_STRING)) return match(type_STRING);
  else if (check(type_CHAR)) return match(type_CHAR);
  else if (check(NOT)) return match(NOT);
  else if (check(BOOL)) return match(BOOL);
  else if (functionPending()) { function(); }
  else if (classPending()) { classFunc(); }
  else if (check(MINUS)) {
    lexeme *m = match(MINUS);
    lexeme *u = unary();
    return cons(UMINUS, m, u);
  }
}

lexeme *modifier(){
  if(check(PLUS)){
    match(PLUS);
    match(PLUS);
    match(VARIABLE);
    return cons("MODIFIER", cons("DPLUS", PLUS, PLUS), VARIABLE);
  }
  else if(check(MINUS)){
    match(MINUS);
    match(MINUS);
    match(VARIABLE);
    return cons("MODIFIER", cons("DMINUS", MINUS, MINUS), VARIABLE);
  }
}

lexeme *varDef(){
  match(LET);
  lexeme *v = match(VARIABLE);
  if (check(EQUALS)) {
    match(EQUALS);
    lexeme *u = unary();
    return cons("VARDEF", v, u);
  }
  return cons("VARDEF", v, NULL);
}

lexeme *classFunc() {

}

lexeme *classDef(){
  match(CLASS);
  lexeme *v = match(VARIABLE);
  if (check(OBRACE)){
    match(OBRACE);
    lexeme *p = optParameterList();
    match(CBRACE);
    lexeme *b = block();
    return cons()
  }
  cons()
}

lexeme *classCall(){

}
lexeme *function();
lexeme *functionDef();
lexeme *functionCall();
lexeme *block();
lexeme *statements();
lexeme *statement();
lexeme *expr();
lexeme *parameters();
lexeme *optParameterList();
lexeme *arguments();
lexeme *optArgList();
lexeme *ifStatement();
lexeme *optElse();
lexeme *loop();
lexeme *forLoop();
lexeme *whileLoop();

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "recognizer.h"

lexeme *current;
FILE *fp;

void display(lexeme *l) {
  printf("%s\n", getType(l));
  
}

void recognizer(FILE *fileName){
  current = lex(fileName); 

  if (programPending()) {
    program();
  }
  printf("\nlegal\n");
}

int main(int argc, char **argv){
  if (argc == 1) {
    printf("%d arguments!\n",argc-1); 
    exit(1);
  }

  fp = fopen(argv[1], "r");
  recognizer(fp);
  fclose(fp);
}

/*
lexical interface functions
*/
int check(char *type){
  return getType(current) == type;
}

void *match(char *type){
  lexeme *temp = current;
  // printf("%s === ", type);
  // display(current);
  // printf("ival: %d, ", getIval(current));
  // // printf("sval: %s, ", getSval(current));
  // printf("rval: %f, ", getRval(current));
  // // printf("kval: %s", getKval(current));
  if (!check(type)) {
    newErrorLexeme("ERROR", "Match error", getLineNum(current));
    printf("\nillegal\n");
    exit(1);
  }
  advance();
  return temp;
}

void advance(){
  current = lex(fp);
}

/*
Pending fuctions
*/
int programPending(){
  return classPending() || varDefPending() || functionPending();
}

int classPending(){
  return classInitPending() || classDefPending() || classInitPending();
}

int classInitPending(){
  return check(NEW);
}

int classDefPending(){
  return check(CLASS);
}

int loopPending(){
  return check(FOR) || check(WHILE);
}

int varDefPending() {
  return check(LET);
}

int functionPending() {
  return funcDefPending() || funcCallPending();
}

int funcDefPending() {
  return check(FUNCTION);
}

int funcCallPending(){
  return check(VARIABLE);
}

int exprPending(){
  return unaryPending() || modifierPending();
}

int unaryPending(){
  return check(VARIABLE) || check(type_INT) || check(type_REAL) || 
    check(type_STRING) || check(type_CHAR) || check(type_BOOL) || 
    check(NOT) || check(MINUS) || funcCallPending();
}

int modifierPending(){
  return check(PLUS) || check(MINUS);
}

int ifPending(){
  return check(IF);
}

int opPending() {
  return check(PLUS) || check(MINUS) || check(EQUALS) || check(TIMES) ||
    check(DIVIDE) || check(EXPONENT) || check(MODULO) || check(AND) ||
    check(OR) ||  check(GTHAN) || check(LTHAN);
}

int statementPending(){
  return exprPending() || ifPending() || loopPending() || functionPending() ||
    classPending() || varDefPending();
}

int parametersPending(){
  return check(VARIABLE);
}

int argumentsPending(){
  return unaryPending() || exprPending();
}

int elsePending(){
  return check(ELSE);
}

/*
Grammar definition functions
*/
lexeme *program(){
  lexeme *d = def();
  if (programPending()) return program();
  lexeme *e = match(END_OF_FILE);
  return cons("PROGRAM", d, e);
}

lexeme *def() {
  if (classPending()) return classFunc(); 
  else if (varDefPending()) return varDef();
  else if (functionPending()) return function();
  return newErrorLexeme("ERROR", "Error in def ", getLineNum(current));
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
  return newErrorLexeme("ERROR", "Error in op", getLineNum(current));
}

lexeme *unary(){
  if (check(VARIABLE)) return match(VARIABLE);
  else if (check(type_INT)) return match(type_INT);
  else if (check(type_REAL)) return match(type_REAL);
  else if (check(type_STRING)) return match(type_STRING);
  else if (check(type_CHAR)) return match(type_CHAR);
  else if (check(NOT)) return match(NOT);
  else if (check(BOOL)) return match(BOOL);
  else if (functionPending()) { return function(); }
  else if (classPending()) { return classFunc(); }
  else if (check(MINUS)) {
    lexeme *m = match(MINUS);
    lexeme *u = unary();
    return cons(UMINUS, m, u);
  }
  return newErrorLexeme(ERROR, "Error in unary", getLineNum(current));
}

lexeme *modifier(){
  if(check(PLUS)){
    lexeme *p1 = match(PLUS);
    lexeme *p2 = match(PLUS);
    lexeme *v = match(VARIABLE);
    return cons(MODIFIER, cons(JOIN, p1, p2), v);
  }
  else if(check(MINUS)){
    lexeme *m1 = match(MINUS);
    lexeme *m2 = match(MINUS);
    lexeme *v = match(VARIABLE);
    return cons(MODIFIER, cons(JOIN, m1, m2), v);
  }
    return newErrorLexeme(ERROR, "Error in modifier", getLineNum(current));
}

lexeme *varDef(){
  match(LET);
  lexeme *v = match(VARIABLE);
  if (check(EQUALS)) {
    match(EQUALS);
    lexeme *u = unary();
    match(SEMI);
    return cons(VAR_DEF, v, u);
  }
  match(SEMI);
  return cons(VAR_DEF, v, NULL);
}

lexeme *classFunc() {
  if (classDefPending()) return classDef();
  else if (classInitPending()) return classInit();
  return newErrorLexeme(ERROR, "Error in class ", getLineNum(current));
}

lexeme *classDef(){
  match(CLASS);
  lexeme *v = match(VARIABLE);
  match(OBRACE);
  lexeme *p = optParameterList();
  match(CBRACE);
  lexeme *b = block();
  return cons(CLASS_DEF, v, cons(JOIN, p, b));
}

lexeme *classInit(){
  match(NEW);
  match(CLASS);
  lexeme *v = match(VARIABLE);
  match(OBRACE);
  lexeme *a = optArgList();
  match(CBRACE);
  return cons(CLASS_INIT, v, a);
}

lexeme *function(){
  if (check(FUNCTION)) return functionDef();
  else if (check(VARIABLE)) return functionCall();
  return newErrorLexeme(ERROR, "Error in function", getLineNum(current));
}

lexeme *functionDef(){
  match(FUNCTION);
  lexeme *f = match(VARIABLE);
  match(OBRACE);
  lexeme *p = optParameterList();
  match(CBRACE);
  lexeme *b = block();
  return cons(FUNC_DEF, f , cons(JOIN, p, b));
}

lexeme *functionCall(){
  lexeme *v = match(VARIABLE);
  match(OBRACE);
  lexeme *a = optArgList();
  match(CBRACE);
  return cons(FUNC_CALL, v, a);
}

lexeme *block(){
  match(BEGIN);
  lexeme *s = statements();
  if(statementPending()) { 
    statements();
  }
  match(END);
  return s;
}

lexeme *statements() {
  lexeme *s = statement();
  if (statementPending()) return statement();
  return s;
}

lexeme *statement(){
  if(exprPending()) return expr();
  else if(ifPending()) return ifStatement();
  else if(loopPending()) return loop();
  else if(functionPending()) return function();
  else if(classPending()) return classFunc();
  else if(varDefPending()) return varDef();
  return newErrorLexeme(ERROR, "Error in statement", getLineNum(current));
}

lexeme *expr(){ //FIX
  lexeme *u2;
  if (unaryPending()) {
    lexeme *u = unary();
    if (opPending()) {
      lexeme *o = op(); // if op is = or ()?
      if (strcmp(getType(o),EQUALS) == 0) {
        if(exprPending()) {
          u2 = expr();
        }
        else {
          u2 = unary();
        }
      }
      if(unaryPending()) {
        u2 = unary();
      }
      return cons(EXPR, u, cons(JOIN, o, u2));
    }
    return u;
  }
  else if(modifierPending()){
    return modifier();
  }
  return newErrorLexeme(ERROR, "Error in expr", getLineNum(current));
}

lexeme *parameters(){
  lexeme *v, *p;
  v = match(VARIABLE);
  if (check(COMMA)) {
    match(COMMA);
    p = parameters();
  }
  else p = NULL;

  return cons(VAR_LIST, v, p);
}

lexeme *optParameterList(){
  if(parametersPending()) return parameters();
  else return NULL;
}

lexeme *arguments(){
  lexeme *u, *a;
  u = unary();
  if (check(COMMA)) {
    match(COMMA);
    a = arguments();
  }
  return cons(VAR_LIST, u, a);
}

lexeme *optArgList(){
  if(argumentsPending()) return arguments();
  else return NULL;
}

lexeme *ifStatement(){
  match(IF);
  match(OBRACE);
  lexeme *e = expr();
  match(CBRACE);
  lexeme *b = block();
  if (elsePending()) {
    lexeme *el = optElse();
    return cons(ELSE, e, cons(JOIN, b, el));
  }
  return cons(IF_ST, e, b);
}

lexeme *optElse(){
  lexeme *e = match(ELSE); //??FIX
  if (ifPending()) {
    lexeme *i = ifStatement();
    return cons(ELSEIF_ST, e, i);
  }
  else {
    lexeme *b = block();
    return cons(ELSE_ST, e, b);
  }
  return newErrorLexeme(ERROR, "Error in optElse", getLineNum(current));
}

lexeme *loop(){
  if (check(FOR)) return forLoop();
  else if (check(WHILE)) return whileLoop();
  return newErrorLexeme(ERROR, "Error in loop", getLineNum(current));
}

lexeme *forLoop() {
  match(FOR);
  match(OBRACE);
  lexeme *x = expr();
  match(TILDE);
  lexeme *y = expr();
  match(TILDE);
  lexeme *z = expr();
  match(CBRACE);
  lexeme *b = block();
  return cons(FOR_LOOP, cons(JOIN, x, y), cons(JOIN, z, b)); //TODO
}

lexeme *whileLoop() {
  match(WHILE);
  match(OBRACE);
  lexeme *e = expr();
  match(CBRACE);
  lexeme *b = block();
  return cons(WHILE_LOOP, e, b); //TODO
}

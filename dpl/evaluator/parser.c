#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "parser.h"


lexeme *current;
FILE *fp;

void display(lexeme *l) {
  printf("%s\n", getType(l));
  
}

lexeme* parse(FILE *fileName){
  current = newLexeme("", 0);
  fp = fileName;
  if (fp == NULL) {printf("FILE IS NULL");}
  current = lex(fileName);

  if (programPending()) {
    lexeme *p = program();
    // displayLexeme(p); //DEBUG
    return p;
  }

}

/*
lexical interface functions
*/
int check(char *type){
  return getType(current) == type;
}

void *match(char *type){
  lexeme *temp = current;
  //DEBUG
  // printf("TEMP type : %s === ", type);
  // printf("*TEMP sval: %s \n", getSval(temp));
  // printf("%s === ", type);
  // display(current);
  // printf("ival: %d, ", getIval(current));
  // printf("sval: %s, ", getSval(current));
  // printf("rval: %f, ", getRval(current));
  // printf("kval: %s\n", getKval(current));
  //DEBUG
  if (!check(type)) {
    newErrorLexeme("ERROR", "Syntax error", current);
    // printf("\nillegal\n");
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
  return funcDefPending() || funcCallPending() || lambdaPending();
}

int funcDefPending() {
  return check(FUNCTION);
}

int funcCallPending(){
  return check(CALL);
}

int lambdaPending(){
  return check(LAMBDA);
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
  return unaryPending() || exprPending() || funcCallPending(); 
}

int elsePending(){
  return check(ELSE);
}

/*
Grammar definition functions
*/
lexeme *program(){
  lexeme *d, *p;
  d = def();
  if (programPending()) { 
    p = program();
  }
  match(END_OF_FILE);
  return cons(PROGRAM, d, p);
}

lexeme *def() {
  if (classPending()) return classFunc(); 
  else if (varDefPending()) return varDef();
  else if (functionPending()) return function();
  return newErrorLexeme(ERROR, "Error in def ", current);
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
  return newErrorLexeme(ERROR, "Error in op", current);
}

lexeme *unary(){
  if (check(VARIABLE)) return match(VARIABLE);
  else if (check(type_INT)) return match(type_INT);
  else if (check(type_REAL)) return match(type_REAL);
  else if (check(type_STRING)) {
    // printf("UNARY: variable type : %s === ", getType(current)); //DEBUG
    // printf("UNARY: *VAR sval: %s \n", getSval(current)); //DEBUG
    return match(type_STRING);
  }
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
  return newErrorLexeme(ERROR, "Error in unary", current);
}

lexeme *modifier(){
  if(check(PLUS)){
    lexeme *p = match(PLUS);
    match(PLUS);
    lexeme *v = match(VARIABLE);
    return cons(MODIFIER, p, v);
  }
  else if(check(MINUS)){
    lexeme *m = match(MINUS);
    match(MINUS);
    lexeme *v = match(VARIABLE);
    return cons(MODIFIER, m, v);
  }
    return newErrorLexeme(ERROR, "Error in modifier", current);
}

lexeme *varDef(){
  match(LET);
  lexeme *v = match(VARIABLE);
  //DEBUG
  // printf("PARSE: vardef:: ");
  // displayLexeme(v);
  //DEBUG
  if (check(EQUALS)) {
    match(EQUALS);
    lexeme *u = unary();
    // printf("variable type : %s === ", getType(u)); //DEBUG
    // printf("*VAR sval: %s \n", getSval(u)); //DEBUG
    return cons(VAR_DEF, v, u);
  }
  return cons(VAR_DEF, v, NULL);
}

lexeme *classFunc() {
  if (classDefPending()) return classDef();
  else if (classInitPending()) return classInit();
  return newErrorLexeme(ERROR, "Error in class ", current);
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

lexeme *lambdaDef(){
  match(LAMBDA);
  match(OBRACE);
  lexeme *p = optParameterList();
  match(CBRACE);
  lexeme *b = block();
  return cons(LAMBDA, NULL, cons(JOIN, p, b));
}

lexeme *function(){
  if (funcDefPending()) return functionDef();
  else if (funcCallPending()) return functionCall();
  else if (lambdaPending()) return lambdaDef();
  return newErrorLexeme(ERROR, "Error in function", current);
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
  match(CALL);
  lexeme *v = match(VARIABLE);
  match(OBRACE);
  lexeme *a = optArgList();
  match(CBRACE);
  return cons(FUNC_CALL, v, a);
}

lexeme *block(){
  match(BEGIN);
  // printf("EVAL BLOCK\n"); //DEBUG
  lexeme *s = statements();
  if(statementPending()) { s = statements(); }
  match(END);
  return s;
}

lexeme *statements() {
  // printf("\tPARSE STATEMENTS\n"); //DEBUG
  lexeme *s = statement();
  lexeme *s2 = NULL;
  if (statementPending())  {
    s2 = statements();
  }
  return cons(STAT, s, s2);
}

lexeme *statement(){
  // printf("\t\tPARSE STATEMENT\n"); //DEBUG
  if(exprPending()) return expr();
  else if(ifPending()) return ifStatement();
  else if(loopPending()) return loop();
  else if(functionPending()) return function();
  else if(classPending()) return classFunc();
  else if(varDefPending()) return varDef();
  return newErrorLexeme(ERROR, "Error in statement", current);
}

lexeme *expr(){ 
  lexeme *u;
  if (modifierPending()){
    return modifier();
  }
  else {
    u = unary();
    if (opPending()) {
      lexeme *o, *u2;
      if (check(EQUALS)){
        o = op();
        if (check(EQUALS)){
          setType(o, EQUALTO);
        }
      }
      else { o = op(); }
      u2 = expr();
      return cons(getType(o), u, u2);
    }
    return u;
  }
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
  if (unaryPending()) {
    u = unary();
    // printf("Unary type : %s === ", getType(u)); //DEBUG 
    // printf("*Unary sval: %s \n", getSval(u)); //DEBUG
    }
  else if (funcCallPending()){
    u = functionCall();
  }
  else {
    u = expr();
  }
  if (check(COMMA)) {
    match(COMMA);
    a = arguments();
  }
  else a = NULL;
  return cons(VAR_LIST, u, a);
}

lexeme *optArgList(){
  if(argumentsPending()) return arguments();
  else return NULL;
}

lexeme *ifStatement(){
  lexeme *e, *b, *el;
  el = NULL;
  match(IF);
  match(OBRACE);
  e = expr();
  match(CBRACE);
  b = block();
  if (elsePending()) {
    el = optElse();
    // b = cons(JOIN, b, el);
  }
  b = cons(JOIN, b, el);
  return cons(IF_ST, e, b);
}

lexeme *optElse(){
  lexeme *e, *b, *el;
  if (check(ELSEIF)) {
    match(ELSEIF);
    match(OBRACE);
    e = expr();
    match(CBRACE);
    b = block();
    if (check(ELSEIF)){
      el = optElse();
      b = cons(JOIN, b, el);
    }
    el = cons(ELSE_ST, e, b);
  }
  else {
    match(ELSE);
    match(OBRACE);
    e = expr();
    match(CBRACE);
    b = block();
  }
  return cons(ELSE_ST, e, cons(JOIN, b, el));
}

lexeme *loop(){
  if (check(FOR)) return forLoop();
  else if (check(WHILE)) return whileLoop();
  return newErrorLexeme(ERROR, "Error in loop", current);
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
  return cons(FOR_LOOP, cons(JOIN, x, cons(JOIN, y, cons(JOIN, z, NULL))), b);
}

lexeme *whileLoop() {
  match(WHILE);
  match(OBRACE);
  lexeme *e = expr();
  match(CBRACE);
  lexeme *b = block();
  return cons(WHILE_LOOP, e, b);
}

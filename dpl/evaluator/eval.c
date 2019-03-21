#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"
#include "lexeme.h"
#include "types.h"
#include "parser.h"
#include "environ.h"

#include "eval.h"

int main(int argc, char *argv){
  //open file to eval
  if (argc == 1) {
    printf("%d arguments!\n",argc-1); 
    exit(1);
  }
  FILE *fp;
  fp = fopen(argv[1], "r");

  lexeme *tree = parse(fp);  
  lexeme *env = createEnv();
  eval(tree, env);

  fclose(fp);
}

lexeme *eval(lexeme *tree, lexeme *env){
  if (getType(tree) == type_INT) { return tree; }
  else if (getType(tree) == type_REAL) { return tree; }
  else if (getType(tree) == type_CHAR) { return tree; }
  else if (getType(tree) == type_STRING) { return tree; }
  else if (getType(tree) == type_BOOL) { return tree; }
  else if (getType(tree) == VARIABLE) {
    return lookupVal(env, tree);
    }
  else if (getType(tree) == PLUS || getType(tree) == MINUS || getType(tree) == TIMES 
            || getType(tree) == DIVIDE || getType(tree) == MODULO || getType(tree) == EXPONENT 
            || getType(tree) == GTHAN || getType(tree) == LTHAN || getType(tree) == EQUALTO) {
    return evalSimpleOp(tree, env);
  }
  else if(getType(tree) == AND || getType(tree) == OR) {
    return evalShortCircuitOp(tree,env);
  }
  else if(getType(tree) == DOT) {
    return evalDot(tree,env);
  }
  else if(getType(tree) == MODIFIER) {
    return evalModifier(tree, env);
  }
  else if (getType(tree) == VAR_DEF) {
    return evalVarDef(tree,env);
  }
  else if (getType(tree) == FUNC_DEF) { 
    return evalFuncDef(tree,env);
  }
  else if (getType(tree) == FUNC_CALL) { 
    return evalCall(tree,env);
  }
  else if (getType(tree) == CLASS_DEF) { 
    return evalClassDef(tree,env);
  }
  else if (getType(tree) == CLASS_INIT) { 
    // TODO: eval Function 
  }
  else if (getType(tree) == BLOCK) {
    return evalBlock(tree, env);
  }
  //if, for, while
  else if (getType(tree) == IF_ST) { 
    return evalIf(tree,env);
  }
  else if (getType(tree) == FOR_LOOP) { 
    return evalFor(tree, env);
  }
  else if (getType(tree) == WHILE_LOOP) {
    return evalWhile(tree, env);
  }


  else {
    //FATAL error
  }
}


/*
Eval helpers
*/
lexeme *evalSimpleOp(lexeme *t, lexeme *env){
  if (getType(t) == PLUS) return evalPlus(t, env);
  if (getType(t) == MINUS) return evalMinus(t,env);
  if (getType(t) == TIMES) return evalTimes(t, env);
  if (getType(t) == DIVIDE) return evalDivide(t, env);
  if (getType(t) == MODULO) return evalModulo(t, env);
  if (getType(t) == EXPONENT) return evalExponent(t, env);
  if (getType(t) == GTHAN) return evalGreaterThan(t, env);
  if (getType(t) == LTHAN) return evalLessThan(t, env);
  if (getType(t) == EQUALTO) return evalEqualTo(t, env);
}

lexeme *evalShortCircuitOp(lexeme *t, lexeme *env){
  if (getType(t) == AND) {

  }
  if (getType(t) == OR){

  }
}

lexeme *evalModifier(lexeme *t, lexeme *env){
  lexeme *left = car(t);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == PLUS) {
    //TODO
  }
  if (getType(left) == MINUS) {
    //TODO
  }
}

lexeme *evalVarDef(lexeme *t, lexeme *env){

}

lexeme *evalFuncDef(lexeme *t, lexeme *env){

}

lexeme *evalCall(lexeme *t, lexeme *env){

}

lexeme *evalClassDef(lexeme *t, lexeme *env){
  return insertEnv(env, car(t), cons("CLOSURE", env, t));
}

lexeme *evalBlock(lexeme *t, lexeme *env){
  lexeme *result;
  while(t != NULL) {
    result = eval(car(t), env);
    t = cdr(t);
  }
  return result;
}

lexeme *evalIf(lexeme *t, lexeme *env){

}

lexeme *evalFor(lexeme *t, lexeme *env){

}

lexeme *evalWhile(lexeme *t, lexeme *env){

}


/*
operation helpers
*/
lexeme *evalPlus(lexeme *t, lexeme *env){
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    // return newIntegerLexeme(left.ival + right.ival, );
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    // return newRealLexeme(left.ival + right.rval);
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    // return newRealLexeme(left.rval + right.rval);
  }
  //TODO other cases?
}

lexeme *evalMinus(lexeme *t, lexeme *env) {
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    // return newIntegerLexeme(left.ival - right.ival);
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    // return newRealLexeme(left.ival - right.rval);
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    // return newRealLexeme(left.rval - right.rval);
  }
  //TODO other cases?
}

lexeme *evalTimes(lexeme *t, lexeme *env) {
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    // return newIntegerLexeme(left.ival * right.ival, );
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    // return newRealLexeme(left.ival * right.rval);
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    // return newRealLexeme(left.rval * right.rval);
  }
  //TODO other cases?
}

lexeme *evalDivide(lexeme *t, lexeme *env) {
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    // return newIntegerLexeme(left.ival / right.ival, );
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    // return newRealLexeme(left.ival / right.rval);
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    // return newRealLexeme(left.rval / right.rval);
  }
  //TODO other cases?
}

lexeme *evalModulo(lexeme *t, lexeme *env){
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    // return newIntegerLexeme(left.ival % right.ival, );
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    // return newRealLexeme(left.ival % right.rval);
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    // return newRealLexeme(left.rval % right.rval);
  }
  //TODO other cases?
}

lexeme *evalExponent(lexeme *t, lexeme *env){
//eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    // return newIntegerLexeme(left.ival ^ right.ival, );
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    // return newRealLexeme(left.ival ^ right.rval);
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    // return newRealLexeme(left.rval ^ right.rval);
  }
  //TODO other cases?
}

/*
comparison helpers
*/
lexeme *evalGreaterThan(lexeme *t, lexeme *env){

}

lexeme *evalLessThan(lexeme *t, lexeme *env){

}

lexeme *evalEqualTo(lexeme *t, lexeme *env){

}

/*

*/

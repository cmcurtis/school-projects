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
  else if(getType(tree) == EQUALS){
    return evalAssignment(tree, env);
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
  return insertEnv(env, car(t), cdr(t));
}

lexeme *evalFuncDef(lexeme *t, lexeme *env){
  lexeme* closure = cons(CLOSURE, env, cons(JOIN, getFuncDefParams(t), cons(JOIN, getFuncDefBody(t), NULL)));
  return insertEnv(env, getFuncDefName(t), closure);
}

lexeme *evalCall(lexeme *t, lexeme *env){
  lexeme* closure = lookupVal(env, car(t));
  lexeme* args = evalArgs(cdr(t), env);
  // if(isBuiltIn(closure)) { return evalBuiltIn(closure, args); }
  lexeme* params = getClosureParams(closure);
  lexeme* body = getClosureBody(closure);
  lexeme* senv = getClosureEnvironment(closure);
  lexeme* eargs = evalArgs(args, env);
  lexeme* xenv = extendEnv(senv, params, eargs);
  return eval(body, xenv);
}

lexeme *evalClassDef(lexeme *t, lexeme *env){
  return insertEnv(env, car(t), cons("CLOSURE", env, t));
}

lexeme *evalAssignment(lexeme *t, lexeme *env){
  //eval the right hand side
  lexeme* value = eval(cdr(t),env);
  if (getType(car(t)) == DOT){
    lexeme* obj = eval(car(car(t)), env);
    updateEnv(obj, car(cdr(t)), value);
    }
  else {
    updateEnv(car(t), value, env);
    }
  return value;
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
  lexeme *e = eval(car(t), env);
  lexeme *b;
  if(getIval(e)){ //if cond is true
    b = car(cdr(t));
    }
  else {
    if (getType(cdr(t)) == JOIN) { //else statement exists
      lexeme *el = cdr(cdr(t));
      lexeme *elVal = eval(car(el), env);
      while (getIval(elVal) == 0){ //else is false
        if(getType(cdr(el)) == JOIN) {
          el = cdr(cdr(el));
          elVal = eval(car(el), env);
        }
        else return;
      }
      b = car(cdr(el));
    }
    else return;
  }
  return eval(b, env);
}

lexeme *evalFor(lexeme *t, lexeme *env){

}

lexeme *evalWhile(lexeme *t, lexeme *env){
  lexeme *e = eval(car(t), env);
  if (getIval(e)){ //TODO: more conditions?
    return eval(cdr(t), env);
  }
  else return;
}


/*
operation helpers
*/
lexeme *evalPlus(lexeme *t, lexeme *env){
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    return newLexemeInt(getIval(left) + getIval(right), getLineNum(left));
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    return newLexemeReal(getIval(left) + getRval(right), getLineNum(left));
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    return newLexemeReal(getRval(left) + getRval(right), getLineNum(left));
  }
  else if(getType(left) == type_REAL && getType(right) == type_INT) {
    return newLexemeReal(getRval(left) + getIval(right), getLineNum(left));
  }
  else {
    //ERROR
  }
}

lexeme *evalMinus(lexeme *t, lexeme *env) {
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    return newLexemeInt(getIval(left) - getIval(right), getLineNum(left));
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    return newLexemeReal(getIval(left) - getRval(right), getLineNum(left));
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    return newLexemeReal(getRval(left) - getRval(right), getLineNum(left));
  }
  else if(getType(left) == type_REAL && getType(right) == type_INT) {
    return newLexemeReal(getRval(left) - getIval(right), getLineNum(left));
  }
  else {
    //ERROR
  }
}

lexeme *evalTimes(lexeme *t, lexeme *env) {
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    return newLexemeInt(getIval(left) * getIval(right), getLineNum(left));
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    return newLexemeReal(getIval(left) * getRval(right), getLineNum(left));
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    return newLexemeReal(getRval(left) * getRval(right), getLineNum(left));
  }
  else if(getType(left) == type_REAL && getType(right) == type_INT) {
    return newLexemeReal(getRval(left) * getIval(right), getLineNum(left));
  }
  else {
    //ERROR
  }
}

lexeme *evalDivide(lexeme *t, lexeme *env) {
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    return newLexemeInt(getIval(left) / getIval(right), getLineNum(left));
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    return newLexemeReal(getIval(left) / getRval(right), getLineNum(left));
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    return newLexemeReal(getRval(left) / getRval(right), getLineNum(left));
  }
  else if(getType(left) == type_REAL && getType(right) == type_INT) {
    return newLexemeReal(getRval(left) / getIval(right), getLineNum(left));
  }
  else {
    //ERROR
  }
}

lexeme *evalModulo(lexeme *t, lexeme *env){
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    return newLexemeInt(getIval(left) % getIval(right), getLineNum(left));
  }
  else{
    //ERROR
  }
}

lexeme *evalExponent(lexeme *t, lexeme *env){
//eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    return newLexemeInt(getIval(left) ^ getIval(right), getLineNum(left));
  }
  // else if (getType(left) == type_INT && getType(right) == type_REAL) {
  //   return newLexemeReal(getIval(left) ^ getRval(right), getLineNum(left));
  // }
  // else if(getType(left) == type_REAL && getType(right) == type_REAL) {
  //   return newLexemeReal(getRval(left) ^ getRval(right), getLineNum(left));
  // }
  // else if(getType(left) == type_REAL && getType(right) == type_INT) {
  //   return newLexemeReal(getRval(left) ^ getIval(right), getLineNum(left));
  // }
  else {
    //ERROR
  }
}

/*
comparison helpers
*/
lexeme *evalGreaterThan(lexeme *t, lexeme *env){
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  int lineNum = getLineNum(left);
  lexeme *b;
  if (getType(left) == type_INT && getType(right) == type_INT) {
    if (getIval(left) > getIval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    if (getIval(left) > getRval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    if (getRval(left) > getRval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if(getType(left) == type_REAL && getType(right) == type_INT) {
    if (getRval(left) > getIval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else {
    //ERROR
  }
  return b;
}

lexeme *evalLessThan(lexeme *t, lexeme *env){
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  int lineNum = getLineNum(left);
  lexeme *b;
  if (getType(left) == type_INT && getType(right) == type_INT) {
    if (getIval(left) < getIval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    if (getIval(left) < getRval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    if (getRval(left) < getRval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if(getType(left) == type_REAL && getType(right) == type_INT) {
    if (getRval(left) < getIval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else {
    //ERROR
  }
  return b;
}

lexeme *evalEqualTo(lexeme *t, lexeme *env){
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  int lineNum = getLineNum(left);
  lexeme *b;
  if (getType(left) == type_INT && getType(right) == type_INT) {
    if (getIval(left) == getIval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    if (getIval(left) == getRval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    if (getRval(left) == getRval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if(getType(left) == type_REAL && getType(right) == type_INT) {
    if (getRval(left) == getIval(right)) { b = newLexmeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else {
    //ERROR
  }
  return b;
}

/*
other eval helpers
*/
lexeme *getFuncDefParams(lexeme *t){ return cdr(car(t)); }
lexeme *getFuncDefBody(lexeme *t){ return cdr(cdr(t)); }
lexeme *getFuncDefName(lexeme *t){ return car(t); }
lexeme *getClosureParams(lexeme *t) { return cdr(car(t)); }
lexeme *getClosureBody(lexeme *t) { return cdr(cdr(t)); }
lexeme *getClosureEnvironment(lexeme *t) { return car(t); }
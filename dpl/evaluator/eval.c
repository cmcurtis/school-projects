//author:  Caley Curtis

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

/*
eval getters
*/
lexeme *getFuncDefParams(lexeme *t);
lexeme *getFuncDefBody(lexeme *t);
lexeme *getFuncDefName(lexeme *t);
lexeme *getClosureParams(lexeme *t);
lexeme *getClosureBody(lexeme *t);
lexeme *getClosureEnvironment(lexeme *t);

/*
built-ins
*/
int isBuiltIn(lexeme *c);
lexeme* evalBuiltIn(lexeme* c, lexeme* args);
lexeme* evalPrintln(lexeme *evaluatedArgList);
lexeme* evalOpenFileForReading(lexeme *evaluatedArgs);
lexeme* evalReadInteger(lexeme *evaluatedArgs);
lexeme* evalAtFileEnd(lexeme *evaluatedArgs);
lexeme* evalCloseFile(lexeme *evaluatedArgs);
lexeme* evalNewArray(lexeme *evalArgs);
lexeme* evalSetArray(lexeme *evaluatedArgList);
lexeme* evalGetArray(lexeme* evaluatedArgList);
lexeme* evalGetArgCount(lexeme *evaluatedArgs);
lexeme* evalGetArg(lexeme *evaluatedArgs);

/*
globals for commandline args
*/
int countCL;
char **argsCL;

int main(int argc, char **argv){
  //open file to eval
  if (argc == 1) {
    printf("%d arguments!\n",argc-1); 
    exit(1);
  }
  countCL = argc;
  argsCL = argv;

  FILE *fp;
  fp = fopen(argv[1], "r");

  lexeme *tree = parse(fp);
  lexeme *env = createEnv();
  //insert builtIns into env
  insertEnv(env, newLexemeKeyword(VARIABLE, "getArg", 0), newLexeme("getArg", 0)); 
  insertEnv(env, newLexemeKeyword(VARIABLE, "getArgCount", 0), newLexeme("getArgCount", 0)); 
  insertEnv(env, newLexemeKeyword(VARIABLE, "PRINT", 0), newLexeme("PRINT", 0)); 
  insertEnv(env, newLexemeKeyword(VARIABLE, "OPEN", 0), newLexeme("OPEN", 0)); 
  insertEnv(env, newLexemeKeyword(VARIABLE, "READ", 0), newLexeme("READ", 0)); 
  insertEnv(env, newLexemeKeyword(VARIABLE, "NOT_FILE_END", 0), newLexeme("NOT_FILE_END", 0)); 
  insertEnv(env, newLexemeKeyword(VARIABLE, "CLOSE", 0), newLexeme("CLOSE", 0)); 
  insertEnv(env, newLexemeKeyword(VARIABLE, "newArray", 0), newLexeme("newArray", 0)); 
  insertEnv(env, newLexemeKeyword(VARIABLE, "setArray", 0), newLexeme("setArray", 0)); 
  insertEnv(env, newLexemeKeyword(VARIABLE, "getArray", 0), newLexeme("getArray", 0)); 


  eval(tree, env);

  fclose(fp);
}

lexeme *eval(lexeme *tree, lexeme *env){
  // printf("\nEVALUATING::");
  // displayLexeme(tree); //DEBUG
  // printf("\nENV::");
  // displayEnv(env); //DEBUG
  // printf("\n");
  if (tree == NULL) { return NULL; }
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
    return evalDot(tree, env);
  }
  else if(getType(tree) == MODIFIER) {
    return evalModifier(tree, env);
  }
  else if (getType(tree) == VAR_DEF) {
    // printf("~variable defintion evaluation~\n"); //DEBUG
    return evalVarDef(tree, env);
  }
  else if (getType(tree) == FUNC_DEF) {
    // printf("~function def evaluation~\n"); //DEBUG
    return evalFuncDef(tree, env);
  }
  else if (getType(tree) == FUNC_CALL) { 
    // printf("~function call evaluation~\n"); //DEBUG
    return evalCall(tree,env);
  }
  else if (getType(tree) == LAMBDA) { 
    return evalLambda(tree,env);
  }
  else if (getType(tree) == LAMBDA_CLOSURE) {
    return evalLambdaClosure(tree, env);
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
  else if (getType(tree) == STAT) {
    // printf("~statement evaluation~\n"); //DEBUG
    return evalStat(tree, env);
  }
  //if, while
  else if (getType(tree) == IF_ST) { 
    return evalIf(tree,env);
  }
  else if (getType(tree) == ELSE_ST) { 
    return evalElse(tree,env);
  }
  else if (getType(tree) == WHILE_LOOP) {
    return evalWhile(tree, env);
  }
  else if(getType(tree) == PROGRAM) {
    return evalProgram(tree, env);
  }
  return NULL;
  // return newErrorLexeme(ERROR, "Semmantic error", tree);
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
  else return newErrorLexeme(ERROR, "Semantic error in SimpleOp", t);
}

lexeme *evalShortCircuitOp(lexeme *t, lexeme *env){
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);

  if (getType(t) == AND) {
    if (getIval(left) == 1 && getIval(right) == 1){
      return newLexemeBool(1, getLineNum(left));
    }
    else return newLexemeBool(0, getLineNum(left));
  }
  else if (getType(t) == OR){
    if (getIval(left) == 1 || getIval(right) == 1){
      return newLexemeBool(1, getLineNum(left));
    }
    else return newLexemeBool(0, getLineNum(left));
  }
  else return newErrorLexeme(ERROR, "Semantic error in short circuit op", t);
}

lexeme *evalModifier(lexeme *t, lexeme *env){
  lexeme *left = car(t);
  lexeme *right = eval(cdr(t), env);
  lexeme *value;
  if (getType(left) == PLUS) {
    if (getType(right) == type_INT) {
      value = newLexemeInt((getIval(right) + 1), getLineNum(t));
      return updateEnv(env, right, value);
      }
    else return newErrorLexeme(ERROR, "Modifier Error", t);
  }
  else if (getType(left) == MINUS) {
    if (getType(right) == type_INT) { 
      value = newLexemeInt((getIval(right) - 1), getLineNum(t)); 
      return updateEnv(env, right, value);
      }
    else return newErrorLexeme(ERROR, "Modifier Error", t);
  }
  else return newErrorLexeme(ERROR, "Modifier Error", t);
}

lexeme *evalVarDef(lexeme *t, lexeme *env){
  return insertEnv(env, car(t), eval(cdr(t),env));
}

lexeme *evalFuncDef(lexeme *t, lexeme *env){
  // displayEnv(env); //DEBUG
  lexeme* closure = cons(CLOSURE, env, cons(JOIN, getFuncDefParams(t), cons(JOIN, getFuncDefBody(t), NULL)));
  return insertEnv(env, getFuncDefName(t), closure);
}

lexeme* evalLambda(lexeme *t, lexeme *env) {
  return cons(LAMBDA_CLOSURE, env, t);
  }

lexeme* evalArgs(lexeme *t, lexeme *env){
  // printf("argument eval\n"); //DEBUG
  lexeme *arg;
  if (t != NULL) { arg = cons(JOIN, eval(car(t), env), evalArgs(cdr(t), env)); }
  else arg = NULL;
  return arg;
}

lexeme *evalLambdaClosure(lexeme *t, lexeme *env){
  lexeme* args = evalArgs(cdr(t), env);
  lexeme* params = getClosureParams(t);
  lexeme* body = getClosureBody(t);
  lexeme* senv = getClosureEnvironment(t);
  // printf("\nEARGS\n"); //DEBUG
  // lexeme* eargs = evalArgs(args, env);
  lexeme* xenv = extendEnv(senv, params, args);
  return eval(body, xenv);
}

lexeme* evalDot(lexeme *t, lexeme *env){
  lexeme* object = eval(car(t), env);
  return eval(cdr(t), object);
}

lexeme *evalCall(lexeme *t, lexeme *env){
  printf("EVAL CALL : %s", getKval(car(t))); //DEBUG
  lexeme* closure = lookupVal(env, car(t));
  lexeme* args = evalArgs(cdr(t), env);
  if(isBuiltIn(car(t))) { return evalBuiltIn(car(t), args); }
  lexeme* params = getClosureParams(closure);
  lexeme* body = getClosureBody(closure);
  lexeme* senv = getClosureEnvironment(closure);
  // printf("\nEARGS\n"); //DEBUG
  // lexeme* eargs = evalArgs(args, env);
  lexeme* xenv = extendEnv(senv, params, args);
  insertEnv(xenv, newLexemeKeyword(VARIABLE,"this", getLineNum(t)), xenv); //for oo
  return eval(body, xenv);
}

lexeme *evalClassDef(lexeme *t, lexeme *env){
  return insertEnv(env, car(t), cons(CLOSURE, env, t));
}

lexeme *evalAssignment(lexeme *t, lexeme *env){
  //eval the right hand side
  // printf("evalAssign\n"); //DEBUG
  lexeme* value = eval(cdr(t),env);
  // displayLexeme(value); //DEBUG
  if (getType(car(t)) == DOT){
    lexeme* obj = eval(car(car(t)), env);
    updateEnv(obj, car(cdr(t)), value);
    }
  else {
    updateEnv(env, car(t), value);
    }
  return value;
}

lexeme *evalBlock(lexeme *t, lexeme *env){
  // printf("evalBlock\n"); //DEBUG
  lexeme *result;
  while(t != NULL) {
    result = eval(car(t), env);
    t = cdr(t);
  }
  return result;
}

lexeme *evalStat(lexeme *t, lexeme *env){
  // printf("evalSTAT\n"); //DEBUG
  lexeme *result;
  while(t != NULL) {
    result = eval(car(t), env);
    t = cdr(t);
  }
  // printf("LASTSTATEMENT ::: %s \n", getType(result)); //DEBUG
  return result;
}

lexeme *evalIf(lexeme *t, lexeme *env){
  // printf("IF :\n"); //DEBUG
  lexeme *e = eval(car(t), env);
  if(getIval(e)){ //if cond is true
    return eval(car(cdr(t)), env);
    }
  else return eval(cdr(cdr(t)), env);
}

lexeme *evalElse(lexeme *t, lexeme *env){
  // printf("IF ELSE:\n"); //DEBUG
  lexeme *e = eval(car(t), env);
  if (getIval(e)) {
    return eval(car(cdr(t)), env);
    }
  else return eval(cdr(cdr(t)), env);
}

lexeme *evalWhile(lexeme *t, lexeme *env){
  // printf("evalWHILE\n"); //DEBUG
  lexeme *b;
  lexeme *e = eval(car(t), env);
  while (getIval(e)){ //TODO: more conditions?
    // printf("condition is true\n"); //DEBUG
    b = eval(cdr(t), env);
    e = eval(car(t), env);
  }
  return b;
}

lexeme *evalProgram(lexeme *t, lexeme *env){
  // printf("evalProgram\n"); //DEBUG
  lexeme *d = eval(car(t), env);
  // displayLexeme(d); // DEBUG
  if (cdr(t) == NULL) {
    return d;
  }
  else return eval(cdr(t), env);
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
  else return newErrorLexeme(ERROR, "Addition error", t);
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
  else return newErrorLexeme(ERROR, "Subtraction error", t);
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
  else return newErrorLexeme(ERROR, "Multiplication error", t);
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
  else return newErrorLexeme(ERROR, "Division error", t);
}

lexeme *evalModulo(lexeme *t, lexeme *env){
  //eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    return newLexemeInt(getIval(left) % getIval(right), getLineNum(left));
  }
  else return newErrorLexeme(ERROR, "Modulo error", t);
}

lexeme *evalExponent(lexeme *t, lexeme *env){
//eval the left and the right hand sides
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    return newLexemeInt(getIval(left) ^ getIval(right), getLineNum(left));
  }
  else return newErrorLexeme(ERROR, "Exponential error", t);
}

/*
comparison helpers
*/
lexeme *evalGreaterThan(lexeme *t, lexeme *env){
  //eval the left and the right hand sides
  // printf("evalGreaterThan\n"); //DEBUG
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  int lineNum = getLineNum(left);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    if (getIval(left) > getIval(right)) return newLexemeBool(1, lineNum);
    else return newLexemeBool(0, lineNum);
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    if (getIval(left) > getRval(right)) return newLexemeBool(1, lineNum);
    else return newLexemeBool(0, lineNum);
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    if (getRval(left) > getRval(right)) return newLexemeBool(1, lineNum);
    else return newLexemeBool(0, lineNum);
  }
  else if(getType(left) == type_REAL && getType(right) == type_INT) {
    if (getRval(left) > getIval(right)) return newLexemeBool(1, lineNum);
    else return newLexemeBool(0, lineNum);
  }
  else return newErrorLexeme(ERROR, "Comparison error", t);
}

lexeme *evalLessThan(lexeme *t, lexeme *env){
  // printf("evalLessThan\n"); //DEBUG
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  int lineNum = getLineNum(left);
  if (getType(left) == type_INT && getType(right) == type_INT) {
    // printf("\tInt < Int\n"); //DEBUG
    if (getIval(left) < getIval(right)) { return newLexemeBool(1, lineNum); }
    else return newLexemeBool(0, lineNum);
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    // printf("\tInt < Real\n"); //DEBUG
    if (getIval(left) < getRval(right)) { return newLexemeBool(1, lineNum); }
    else return newLexemeBool(0, lineNum);
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    // printf("\tReal < Real\n"); //DEBUG
    if (getRval(left) < getRval(right)) return newLexemeBool(1, lineNum);
    else return newLexemeBool(0, lineNum);
  }
  else if(getType(left) == type_REAL && getType(right) == type_INT) {
    // printf("\tReal < Real\n"); //DEBUG
    if (getRval(left) < getIval(right)) return newLexemeBool(1, lineNum);
    else return newLexemeBool(0, lineNum);
  }
  else return newErrorLexeme(ERROR, "Comparison error", t);
}

lexeme *evalEqualTo(lexeme *t, lexeme *env){
  lexeme *left = eval(car(t), env);
  lexeme *right = eval(cdr(t), env);
  int lineNum = getLineNum(left);
  lexeme *b;
  if (getType(left) == type_INT && getType(right) == type_INT) {
    if (getIval(left) == getIval(right)) { b = newLexemeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if (getType(left) == type_INT && getType(right) == type_REAL) {
    if (getIval(left) == getRval(right)) { b = newLexemeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if(getType(left) == type_REAL && getType(right) == type_REAL) {
    if (getRval(left) == getRval(right)) { b = newLexemeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else if(getType(left) == type_REAL && getType(right) == type_INT) {
    if (getRval(left) == getIval(right)) { b = newLexemeBool(1, lineNum); }
    else { b = newLexemeBool(0, lineNum); }
  }
  else return newErrorLexeme(ERROR, "Comparison error", t);
  return b;
}

/*
eval getters
*/
lexeme *getFuncDefParams(lexeme *t) { return car(cdr(t)); }
lexeme *getFuncDefBody(lexeme *t) { return cdr(cdr(t)); }
lexeme *getFuncDefName(lexeme *t) { return car(t); }
lexeme *getClosureParams(lexeme *t) { return car(cdr(t)); }
lexeme *getClosureBody(lexeme *t) { return car(cdr(cdr(t))); }
lexeme *getClosureEnvironment(lexeme *t) { return car(t); }

/*
built-ins
*/
int isBuiltIn(lexeme *c){
  char* func = getKval(c);
  // printf("\nisBUILTIN::FUNCTION NAME:: %s\n", func); //DEBUG
  if (strcmp(func, "PRINT") == 0 || strcmp(func, "OPEN") == 0 || strcmp(func, "CLOSE") == 0 || strcmp(func, "READ") == 0
    || (strcmp(func, "NOT_FILE_END") == 0) || (strcmp(func, "newArray") == 0) || (strcmp(func, "setArray") == 0) 
    || (strcmp(func, "getArray") == 0) || (strcmp(func, "getArg") == 0) || (strcmp(func, "getArgCount") == 0)){
      return 1;
    }
  else return 0;
}

lexeme* evalBuiltIn(lexeme* c, lexeme* args){
  // printf("EvaluatingBuiltIns\n"); //DEBUG
  char* func = getKval(c);
  if(strcmp(func, "getArg") == 0) { return evalGetArg(args); }
  else if(strcmp(func, "getArgCount") == 0) { return evalGetArgCount(args); }
  else if (strcmp(func, "PRINT") == 0) { return evalPrintln(args); }
  else if(strcmp(func, "OPEN") == 0) { return evalOpenFileForReading(args); }
  else if(strcmp(func, "CLOSE") == 0) { return evalCloseFile(args); }
  else if(strcmp(func, "READ") == 0) { return evalReadInteger(args); }
  else if(strcmp(func, "NOT_FILE_END") == 0) { return evalAtFileEnd(args); }
  else if(strcmp(func, "newArray") == 0) { return evalNewArray(args); }
  else if(strcmp(func, "setArray") == 0) { return evalSetArray(args); }
  else if(strcmp(func, "getArray") == 0) { return evalGetArray(args); }
  else return newErrorLexeme(ERROR, "Error with Builtin", c);
}

lexeme* evalPrintln(lexeme *evaluatedArgList) {
  while (evaluatedArgList != NULL) {
    displayLexeme(evaluatedArgList);//DEBUG
    displayLexeme(car(evaluatedArgList));
    evaluatedArgList = cdr(evaluatedArgList);
    }
  printf("\n");
  return newLexemeBool(1, 0);
  }

lexeme* evalOpenFileForReading(lexeme *evaluatedArgs) {
  lexeme *fileName = car(evaluatedArgs);
  lexeme *fp = newLexeme(FILE_POINTER, getLineNum(evaluatedArgs));
  setFval(fp, fopen(getSval(fileName),"r"));
  return fp;
  }

lexeme* evalReadInteger(lexeme *evaluatedArgs) {
  FILE* filePointer = getFval(car(evaluatedArgs));
  int x;
  fscanf (filePointer, "%d", &x); 
  return newLexemeInt(x, getLineNum(evaluatedArgs));
  }

lexeme* evalAtFileEnd(lexeme *evaluatedArgs) {
  FILE* filePointer = getFval(car(evaluatedArgs));
  if (feof(filePointer)) { return newLexemeBool(0, 0); }
  else { return newLexemeBool(1, 0); }
  }

lexeme* evalCloseFile(lexeme *evaluatedArgs) {
  FILE* filePointer = getFval(car(evaluatedArgs));
  fclose(filePointer);
  return newLexemeBool(1, 0);
  }

//TODO: FIX
int length(lexeme* list){
  int i = 0;
  lexeme* temp = list;
  while (temp != NULL) {
    if (car(temp) == NULL) { i = i + 1; }
    cdr(temp);
  }
  return i;
}

lexeme* evalNewArray(lexeme *evalArgs) {
  // printf("eval new array\n"); //DEBUG
  // assert(length(evalArgs) == 1);  //ensure only one argument
  lexeme* size = car(evalArgs);
  // printf("Size of Array == %i", getIval(size)); //DEBUG
  assert(getType(size) == type_INT);          //ensure an integer argument
  lexeme* a = newLexeme(ARRAY, getLineNum(size));
  newAval(a, getIval(size));        //allocate the array
  assert(getAval(a) != NULL);                //ensure a good allocation
  return a;
  }

lexeme* evalSetArray(lexeme *evaluatedArgList) {
  // printf("eval set array\n"); //DEBUG
  // assert(length(evaluatedArgList) == 3);
  lexeme* a = car(evaluatedArgList);
  lexeme* i = car(cdr(evaluatedArgList));
  lexeme* v = car(cdr(cdr(evaluatedArgList)));
  lexeme** array = getAval(a);
  //check for valid types here
  array[getIval(i)] = v;
  return v;
}

lexeme* evalGetArray(lexeme* evaluatedArgList) {
  // printf("eval get array\n"); //DEBUG
  // assert(length(evaluatedArgList) == 2);
  lexeme* a = car(evaluatedArgList);
  lexeme* i = car(cdr(evaluatedArgList));
  lexeme** array = getAval(a);
  //check for valid types here
  return array[getIval(i)];
}

lexeme* evalGetArgCount(lexeme* evaluatedArgs) {
  return newLexemeInt(countCL, 0);
}

lexeme* evalGetArg(lexeme* evaluatedArgs) { 
  lexeme* index = car(evaluatedArgs);
  return newLexemeChar(type_STRING, argsCL[getIval(index)], getLineNum(index));
  }
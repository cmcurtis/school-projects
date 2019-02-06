#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"
#include "lexeme.h"
#include "types.h"


//Pending Functions
int programPending();
int classPending();
int classInitPending();
int classDefPending();
int classCallPending();
int varDefPending();
int functionPending();
int funcDefPending();
int funcCallPending();
int exprPending();
int unaryPending();
int modifierPending();
int ifPending();
int opPending();
int loopPending();
int statementPending();
int parametersPending();
int argumentsPending();
int elsePending(); 

//Check and Match Functions
int check(char *type);
void *match(char *type); //return lexeme for parsing
void advance();
// lexeme *cons(char *type, lexeme *left, lexeme *right);

//Rule functions: return lists for parsing
lexeme *program();
lexeme *def();
lexeme *op();
lexeme *unary();
lexeme *modifier();
lexeme *varDef();
lexeme *classFunc();
lexeme *classInit();
lexeme *classDef();
lexeme *classCall();
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

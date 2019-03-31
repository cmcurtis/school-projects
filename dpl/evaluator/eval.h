#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexeme.h"
#include "types.h"

extern lexeme *eval(lexeme *tree, lexeme *env);

lexeme *evalSimpleOp(lexeme *tree, lexeme *env);
lexeme *evalShortCircuitOp(lexeme *tree, lexeme *env);
lexeme *evalModifier(lexeme *tree, lexeme *env);
lexeme *evalVarDef(lexeme *tree, lexeme *env);
lexeme *evalAssignment(lexeme *tree, lexeme *env);
lexeme *evalFuncDef(lexeme *tree, lexeme *env);
lexeme *evalCall(lexeme *tree, lexeme *env);
lexeme *evalClassDef(lexeme *tree, lexeme *env);
lexeme* evalLambda(lexeme *tree, lexeme *env);
lexeme *evalBlock(lexeme *tree, lexeme *env);
lexeme *evalStat(lexeme *tree, lexeme *env);
lexeme *evalIf(lexeme *tree, lexeme *env);
lexeme *evalElse(lexeme *tree, lexeme *env);
lexeme *evalWhile(lexeme *tree, lexeme *env);
lexeme *evalProgram(lexeme *tree, lexeme *env);


//operation helpers
lexeme *evalPlus(lexeme *tree, lexeme *env);
lexeme *evalMinus(lexeme *tree, lexeme *env);
lexeme *evalTimes(lexeme *tree, lexeme *env);
lexeme *evalDivide(lexeme *tree, lexeme *env);
lexeme *evalModulo(lexeme *tree, lexeme *env);
lexeme *evalExponent(lexeme *tree, lexeme *env);

//comparison helpers
lexeme *evalGreaterThan(lexeme *tree, lexeme *env);
lexeme *evalLessThan(lexeme *tree, lexeme *env);
lexeme *evalEqualTo(lexeme *tree, lexeme *env);

// and or
lexeme *evalShortCircuitOp(lexeme *tree, lexeme *env);
lexeme *evalDot(lexeme *tree, lexeme *env);
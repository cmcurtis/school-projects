#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexeme.h"

extern lexeme *createEnv();
extern lexeme *lookupVal(lexeme *env, lexeme *id);
extern lexeme *updateEnv(lexeme *env, lexeme *id, lexeme *val);
extern lexeme *insertEnv(lexeme *env, lexeme *id, lexeme *val);
extern lexeme *extendEnv(lexeme *env, lexeme *vars, lexeme *vals);


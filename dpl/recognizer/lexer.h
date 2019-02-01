//author:  Caley Curtis

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "lexeme.h"

typedef struct Lexer lexer;

lexeme *lex(FILE *fp);
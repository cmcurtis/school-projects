//author:  Caley Curtis

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lexeme lexeme;

extern char *getType(lexeme *l);

extern lexeme *newLexeme(char *t);

extern lexeme *newErrorLexeme(char *err, char *message);

extern lexeme *newLexemeInt(int x);

extern lexeme *newLexemeReal(double x);

extern lexeme *newLexemeChar(char *type, char *x);

extern lexeme *newLexemeKeyword(char *type, char *x);

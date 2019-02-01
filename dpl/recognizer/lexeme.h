//author:  Caley Curtis

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lexeme lexeme;

extern char *getType(lexeme *l);
extern int getLineNum(lexeme *l);

extern void setLeftLex(lexeme *x, lexeme *l);
extern void setRightLex(lexeme *x, lexeme *r);

extern lexeme *newLexeme(char *t, int n);

extern lexeme *newErrorLexeme(char *err, char *message, int n);

extern lexeme *newLexemeInt(int x, int n);

extern lexeme *newLexemeReal(double x, int n);

extern lexeme *newLexemeChar(char *type, char *x, int n);

extern lexeme *newLexemeKeyword(char *type, char *x, int n);

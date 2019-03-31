//author:  Caley Curtis

#include <stdlib.h>
#include <string.h>

//Punctuation
extern char *OPAREN; 
extern char *CPAREN;
extern char *OBRACE;
extern char *CBRACE; 
extern char *COMMA;
extern char *TILDE;
extern char *COLON;
extern char *DQUOTE;
extern char *SEMI;

// Operators
extern char *PLUS;
extern char *MINUS;
extern char *EQUALS;
extern char *DIVIDE;
extern char *TIMES;
extern char *GTHAN;
extern char *LTHAN;
extern char *NOT;
extern char *EXPONENT;
extern char *MODULO;
extern char *AND;
extern char *OR;
extern char *DOT;
extern char *EQUALTO;

// Keywords 
extern char *BEGIN;
extern char *END;
extern char *LET;
extern char *INT;
extern char *REAL;
extern char *CHAR;
extern char *STRING;
extern char *BOOL;
extern char *CLASS;
extern char *IF;
extern char *ELSEIF;
extern char *ELSE;
extern char *WHILE;
extern char *FOR;
extern char *NEW;
extern char *FUNCTION;
extern char *DEFINE;
extern char *CALL;

// types
extern char *type_INT;
extern char *type_REAL;
extern char *type_CHAR;
extern char *type_STRING;
extern char *type_BOOL;
extern char *VARIABLE;
extern char *UMINUS;
extern char *END_OF_FILE;

//types for building parse trees
extern char *ERROR;
extern char *JOIN;
extern char *CLOSURE;
extern char *ENV;
extern char *TABLE;
extern char *PROGRAM;
extern char *CLASS_DEF;
extern char *CLASS_INIT;
extern char *FUNC_DEF;
extern char *FUNC_CALL;
extern char *LAMBDA;
extern char *VAR_DEF;
extern char *ASSIGN;
extern char *MODIFIER;
extern char *EXPR;
extern char *VAR_LIST;
extern char *STAT;
extern char *BLOCK;
extern char *IF_ST;
extern char *ELSE_ST;
extern char *ELSEIF_ST;
extern char *FOR_LOOP;
extern char *FILE_POINTER;
extern char *WHILE_LOOP;
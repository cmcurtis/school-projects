//author:  Caley Curtis

#include <stdlib.h>
#include <string.h>
#include "types.h"

//Punctuation
char *OPAREN = "OPAREN"; 
char *CPAREN = "CPAREN";
char *OBRACE = "OBRACE";
char *CBRACE = "CBRACE"; 
char *COMMA = "COMMA";
char *TILDE = "TILDE";
char *COLON = "COLON";
char *DQUOTE = "DQOUTE";
char *SEMI = "SEMI";

// Operators
char *PLUS = "PLUS";
char *MINUS = "MINUS";
char *EQUALS = "EQUALS";
char *DIVIDE = "DIVIDE";
char *TIMES = "TIMES";
char *GTHAN = "GTHAN";
char *LTHAN = "LTHAN";
char *NOT = "NOT";
char *EXPONENT = "EXPONENT";
char *MODULO = "MODULO";
char *AND = "AND";
char *OR = "OR";
char *DOT = "DOT";
char *EQUALTO = "EQUALTO";
char *SET = "SET";
char *GET = "GET";

// Keywords 
char *BEGIN = "BEGIN";
char *END = "END";
char *LET = "LET";
char *INT = "INT";
char *REAL = "REAL";
char *CHAR = "CHAR";
char *STRING = "STRING";
char *BOOL = "BOOL";
char *CLASS = "CLASS";
char *IF = "IF";
char *ELSEIF = "ELSEIF";
char *ELSE = "ELSE";
char *WHILE = "WHILE";
char *FOR = "FOR";
char *NEW = "NEW";
char *FUNCTION = "FUNCTION";
char *DEFINE = "DEFINE";
char *CALL = "CALL";
char *ARRAY = "ARRAY";
char *SET_ARRAY = "SET_ARRAY";

// types
char *type_INT = "type_INT";
char *type_REAL = "type_REAL";
char *type_CHAR = "type_CHAR";
char *type_STRING = "type_STRING";
char *type_BOOL = "type_BOOL";
char *VARIABLE = "VARIABLE";
char *UMINUS = "UMINUS";
char *END_OF_FILE = "ENDofINPUT";

//types for building parse trees
char *ERROR = "ERROR";
char *JOIN = "JOIN";
char *CLOSURE = "CLOSURE";
char *ENV = "ENV";
char *TABLE = "TABLE";
char *PROGRAM = "PROGRAM";
char *CLASS_DEF = "CLASS_DEF";
char *CLASS_INIT = "CLASS_INIT";
char *FUNC_DEF = "FUNC_DEF";
char *FUNC_CALL = "FUNC_CALL";
char *LAMBDA = "LAMBDA";
char *VAR_DEF = "VAR_DEF";
char *ASSIGN = "ASSIGN";
char *MODIFIER = "MODIFIER";
char *EXPR = "EXPR";
char *VAR_LIST = "VAR_LIST";
char *STAT = "STAT";
char *BLOCK = "BLOCK";
char *IF_ST = "IF_ST";
char *ELSE_ST = "ELSE_ST";
char *ELSEIF_ST = "ELSEIF_ST";
char *FOR_LOOP = "FOR_LOOP";
char *WHILE_LOOP = "WHILE_LOOP";
char *FILE_POINTER = "FILE_POINTER";
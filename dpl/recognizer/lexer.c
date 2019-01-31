//author:  Caley Curtis

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "types.h"
#include "lexeme.h"
#include "lexer.h"

int lineNumber = 1;
int CharacterHasBeenPushed = 0;
char PushbackChar;

void append(char *s, char c)
  {
  int len = strlen(s);
  s[len] = c;
  s[len + 1] = '\0';
  }

//Reading helpers
char readChar(FILE *fp) {
  char ch = fgetc(fp);
  if (ch == '\n') ++lineNumber;
  return ch;
  }

char myRead(FILE *fp)
    {
    if (CharacterHasBeenPushed)
        {
        // printf("getting pushed character\n");
        CharacterHasBeenPushed = 0;
        // return PushbackChar
        char tmp = PushbackChar;
        PushbackChar = '\0';
        return tmp;
        }
    else
        return readChar(fp);
    }

void myPushback(char ch)
    {
    // printf("pushback char: %c\n", PushbackChar);
    // printf("HasBeenPushed: %d\n", CharacterHasBeenPushed);
    if (CharacterHasBeenPushed) {
      printf("too many pushbacks\n");
      exit(1);
    }
    CharacterHasBeenPushed = 1;
    PushbackChar = ch;
    }

void skipWhiteSpace(FILE *fp)
  {
  char ch;
  // ch = fgetc(fp);
  ch = myRead(fp);
  while (isspace(ch))
      ch = readChar(fp);
  myPushback(ch);
  }

//lexing helpers
lexeme *lexVariableOrKeyword(FILE *fp) {
  char ch;
  char token[30] = {0};
  
  ch = myRead(fp);
  while (isalpha(ch) || isdigit(ch)){
    append(token, ch);
    ch = myRead(fp);
    }
  // printf("ch: %c\n", ch);
  myPushback(ch);

  if (strcmp(token,"if") == 0) return newLexemeKeyword(IF, "if");
  else if (strcmp(token,"elseif") == 0) return newLexemeKeyword(ELSEIF, "elseif");
  else if (strcmp(token,"else") == 0) return newLexemeKeyword(ELSE, "else");
  else if (strcmp(token,"while") == 0) return newLexemeKeyword(WHILE, "while");
  else if (strcmp(token,"let") == 0) return newLexemeKeyword(LET, "let");
  else if (strcmp(token,"int") == 0) return newLexemeKeyword(INT, "int");
  else if (strcmp(token,"real") == 0) return newLexemeKeyword(REAL, "real");
  else if (strcmp(token,"char") == 0) return newLexemeKeyword(CHAR, "char");
  else if (strcmp(token,"string") == 0) return newLexemeKeyword(STRING, "string");
  else if (strcmp(token,"bool") == 0) return newLexemeKeyword(BOOL, "bool");
  else if (strcmp(token,"BEGIN") == 0) return newLexemeKeyword(BEGIN, "BEGIN");
  else if (strcmp(token,"END") == 0) return newLexemeKeyword(END, "END");
  else 
    return newLexemeKeyword(VARIABLE, token);
}

lexeme *lexNumber(FILE *fp) {
  int real = 0;
  char* buffer = malloc(sizeof(char[64]));
  char ch = myRead(fp);

  while(!EOF && (isdigit(ch)|| ch == '.')) {
    buffer += ch;
    if(ch == '.' && real) { 
      printf("Bad Number @ line %d", lineNumber);
      exit(1); }
    if(ch == '.') real = 1;
    ch = myRead(fp);
  }
  // myPushback(ch);
  if (real) return newLexemeReal(atof(buffer));
  else return newLexemeInt(atoi(buffer));
}

lexeme *lexString(FILE *fp) {
  char* buffer = malloc(sizeof(char[64]));
  char ch = myRead(fp);

  while(!EOF && ch != '\"') {
    buffer += ch;
    ch = myRead(fp);
  }
  // myPushback(ch);
  return newLexemeChar(type_STRING, buffer);
}

lexeme *lex(FILE *fp)
  {
  char ch;
  skipWhiteSpace(fp);
  
  ch = myRead(fp); 
  // printf("test: %c\n", ch);

  if (ch == EOF) 
  {
  // printf("EOF: %c", ch);
  return newLexeme(END_OF_FILE);
  }

  switch(ch) 
    { 
    // single character tokens 

    case '(': return newLexeme(OPAREN); 
    case ')': return newLexeme(CPAREN); 
    case ',': return newLexeme(COMMA); 
    case '+': return newLexeme(PLUS);
    case '*': return newLexeme(TIMES); 
    case '-': return newLexeme(MINUS); 
    case '/': return newLexeme(DIVIDE); 
    case '<': return newLexeme(LTHAN); 
    case '>': return newLexeme(GTHAN); 
    case '=': return newLexeme(EQUALS); 
    case '{': return newLexeme(OBRACE);
    case '}': return newLexeme(CBRACE);
    case '!': return newLexeme(NOT);
    case '~': return newLexeme(TILDE);

    default: 
      if (isdigit(ch)) 
        { 
        myPushback(ch); 
        return lexNumber(fp); 
        } 
      else if (isalpha(ch)) 
        {
        myPushback(ch);
        return lexVariableOrKeyword(fp);
        } 
      else if (ch == '\"') 
        { 
        return lexString(fp); 
        } 
      else
        printf("Fatal Error @ line %d", lineNumber);
        exit(1); 
    }
  }


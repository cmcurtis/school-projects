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

int lineNumber = 0;
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
        CharacterHasBeenPushed = 0;
        char tmp = PushbackChar;
        PushbackChar = '\0';
        return tmp;
        }
    else
        return readChar(fp);
    }

void myPushback(char ch)
    {
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
  while (isalpha(ch) || isdigit(ch) || ch == '_'){
    append(token, ch);
    ch = myRead(fp);
    }
  // printf("ch: %c\n", ch);
  myPushback(ch);

  if (strcmp(token,"if") == 0) return newLexemeKeyword(IF, "IF", lineNumber);
  else if (strcmp(token,"else_if") == 0) return newLexemeKeyword(ELSEIF, "else_if", lineNumber);
  else if (strcmp(token,"else") == 0) return newLexemeKeyword(ELSE, "else", lineNumber);
  else if (strcmp(token,"for") == 0) return newLexemeKeyword(FOR, "for", lineNumber);
  else if (strcmp(token,"while") == 0) return newLexemeKeyword(WHILE, "while", lineNumber);
  else if (strcmp(token,"let") == 0) return newLexemeKeyword(LET, "let", lineNumber);
  else if (strcmp(token,"int") == 0) return newLexemeKeyword(INT, "int", lineNumber);
  else if (strcmp(token,"real") == 0) return newLexemeKeyword(REAL, "real", lineNumber);
  else if (strcmp(token,"char") == 0) return newLexemeKeyword(CHAR, "char", lineNumber);
  else if (strcmp(token,"string") == 0) return newLexemeKeyword(STRING, "string", lineNumber);
  else if (strcmp(token,"bool") == 0) return newLexemeKeyword(BOOL, "bool", lineNumber);
  else if (strcmp(token,"BEGIN") == 0) return newLexemeKeyword(BEGIN, "BEGIN", lineNumber);
  else if (strcmp(token,"END") == 0) return newLexemeKeyword(END, "END", lineNumber);
  else if (strcmp(token,"function") == 0) return newLexemeKeyword(FUNCTION, "function", lineNumber);
  else if (strcmp(token,"lambda") == 0) return newLexemeKeyword(LAMBDA, "lamdba", lineNumber);
  else if (strcmp(token,"class") == 0) return newLexemeKeyword(CLASS, "class", lineNumber);
  else if (strcmp(token,"call") == 0) return newLexemeKeyword(CALL, "call", lineNumber);
  else if (strcmp(token,"new") == 0) return newLexemeKeyword(NEW, "new", lineNumber);
  else 
    return newLexemeKeyword(VARIABLE, token, lineNumber);
}

lexeme *lexNumber(FILE *fp) {
  int real = 0;
  char* buffer = malloc(sizeof(char[64]));
  char ch = myRead(fp);
  // printf("ch: %c ", ch);

  while(ch != EOF && (isdigit(ch) || ch == '.')) {
    append(buffer, ch);
    // printf("buffer: %s", buffer);
    if(ch == '.' && real) { 
      return newErrorLexeme("ERROR", "Bad Number", lineNumber);
      }
    if(ch == '.') real = 1;
    ch = myRead(fp);
  }
  myPushback(ch);
  if (real) return newLexemeReal(atof(buffer), lineNumber);
  else return newLexemeInt(atoi(buffer), lineNumber);
}

lexeme *lexString(FILE *fp) {
  char* buffer = malloc(sizeof(char[64]));
  char ch = myRead(fp);

  while(!EOF && ch != '\"') {
    append(buffer, ch);
    ch = myRead(fp);
  }
  myPushback(ch);
  return newLexemeChar(type_STRING, buffer, lineNumber);
}

void lexComment(FILE *fp){
  char ch = myRead(fp);

  while(!EOF && ch != '#') {
    ch = myRead(fp);
  }
  return;
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
  return newLexeme(END_OF_FILE, lineNumber);
  }

  switch(ch) 
    { 
    // single character tokens 
    case '(': return newLexeme(OPAREN, lineNumber); 
    case ')': return newLexeme(CPAREN, lineNumber); 
    case ',': return newLexeme(COMMA, lineNumber); 
    case '+': return newLexeme(PLUS, lineNumber);
    case '*': return newLexeme(TIMES, lineNumber); 
    case '-': return newLexeme(MINUS, lineNumber); 
    case '/': return newLexeme(DIVIDE, lineNumber); 
    case '<': return newLexeme(LTHAN, lineNumber); 
    case '>': return newLexeme(GTHAN, lineNumber); 
    case '=': return newLexeme(EQUALS, lineNumber); 
    case '{': return newLexeme(OBRACE, lineNumber);
    case '}': return newLexeme(CBRACE, lineNumber);
    case '!': return newLexeme(NOT, lineNumber);
    case ';': return newLexeme(SEMI, lineNumber);
    case '~': return newLexeme(TILDE, lineNumber);

    default: 
      if (isdigit(ch)) { 
        myPushback(ch);
        return lexNumber(fp); 
      } 
      else if (isalpha(ch)){
        myPushback(ch);
        return lexVariableOrKeyword(fp);
      } 
      else if (ch == '\"'){ 
        return lexString(fp); 
      } 
      else if (ch == '#'){
        lexComment(fp);
      }
      else
        printf("Fatal Error @ line %d", lineNumber);
        exit(1); 
    }
  }

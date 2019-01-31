#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"
#include "lexeme.h"
#include "types.h"

void display(lexeme *l) {
  printf("%s\n", getType(l));
  
}

void scanner(FILE *fileName){ 
  lexeme *token; 
  token = newLexeme("BLANK");

  token = lex(fileName); 
  while (getType(token)) 
      { 
      display(token);
      if (getType(token) == END_OF_FILE) break;
      token = lex(fileName);
      }
  // display(newLexeme(END_OF_FILE));
  }

int main(int argc, char **argv){
  if (argc == 1) {
    printf("%d arguments!\n",argc-1); 
    exit(1);
  }

  FILE *fp;
  fp = fopen(argv[1], "r");
  scanner(fp);
  fclose(fp);
}


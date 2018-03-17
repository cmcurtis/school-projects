#include "string.h"
#include <stdlib.h>
#include <string.h>

char *cleanString(char *x) 
    {
    char *orig = x;
    char *cleaned = x;
    
    while(isspace((unsigned char)*orig)) { orig++; }
    do 
        {
        if (isspace((unsigned char)*orig))
            {
            while(isspace((unsigned char)*orig) && isspace((unsigned char)*(orig+1)))
                {
                orig++;
                }
            *cleaned++ = ' ';
            }
        else if (isalpha((unsigned char)*orig) || *orig == 0) 
            {
            *cleaned++ = tolower((unsigned char)*orig);
            }
        } while(*orig++ != 0);
    return x;
    }


int
main(int argc,char **argv)
    {
    char *s = argv[1];
    s = cleanString(s);
    printf("%s\n", s);
    return;
    }
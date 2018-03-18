#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"
#include "string.h"
#include "gst.h"
#include "avl.h"


/* options */
int verbose = 0;
int treeType = 0;

static int processOptions(int,char **);
static char *cleanString(char *ch);
void Fatal(char *,...);

int
main(int argc,char **argv)
    {

    if (argc == 1) Fatal("%d arguments!\n",argc-1);

    processOptions(argc,argv);

    FILE *corp;
    corp = fopen(argv[argc - 2], "r");

    FILE *command;
    command = fopen(argv[argc - 1], "r");

    if (verbose) 
        {
        printf("Written by Caley Curtis\n");
        return 0;   
        }

    if (treeType) // gst
        {
        GST *g = newGST(displaySTRING, compareSTRING, freeSTRING);
        char *x;
        if (stringPending(corp)) 
            {
            x = readString(corp);
            }
        else 
            {
            x = readToken(corp);
            }
        while (!feof(corp))
            {
            cleanString(x);
            insertGST(g, newSTRING(x));
            if (stringPending(corp)) 
                {
                x = readString(corp);
                }
            else 
                {
                x = readToken(corp);
                }
            }
        fclose(corp);

        while(!feof(command))
            {
            if (stringPending(command)) 
                {
                x = readString(command);
                }
            else 
                {
                x = readToken(command);
                }
            if (strcmp(x, "i") == 0) //insert
                {
                if (stringPending(command)) 
                    {
                    x = readString(command);
                    }
                else 
                    {
                    x = readToken(command);
                    }
                insertAVL(a, newSTRING(x));
                continue;
                }
            else if(strcmp(x, "d") == 0) //delete
                {
                    if (stringPending(command)) 
                        {
                        x = readString(command);
                        }
                    else 
                        {
                        x = readToken(command);
                        }
                    deleteAVL(a, newSTRING(x));
                continue;
                }
            else if (strcmp(x, "f") == 0) //return frequency
                {
                if (stringPending(command)) 
                    {
                    x = readString(command);
                    }
                else 
                    {
                    x = readToken(command);
                    }
                int count = findAVLcount(a, newSTRING(x));
                printf("Frequency of %s: %d\n", x, count);
                continue;
                }
            else if (strcmp(x, "s") == 0) //display tree
                {   
                displayAVL(g, stdout);
                continue;
                }
            else if(strcmp(x, "r") == 0) //display stats
                {
                statisticsAVL(g, stdout);
                continue;
                }
            }
        fclose(command);
        }

    else //avl
        {
        AVL *a = newAVL(displaySTRING, compareSTRING, freeSTRING);
        char *x;
        if (stringPending(corp)) 
            {
            cleanString(x);
            x = readString(corp);
            }
        else 
            {
            x = readToken(corp);
            }
        while (!feof(corp))
            {
            insertAVL(a, newSTRING(x));
            if (stringPending(corp)) 
                {
                x = readString(corp);
                }
            else 
                {
                x = readToken(corp);
                }
            }
        fclose(corp);

        while(!feof(command))
            {
            if (stringPending(command)) 
                {
                x = readString(command);
                }
            else 
                {
                x = readToken(command);
                }
            if (strcmp(x, "i") == 0) //insert
                {
                if (stringPending(command)) 
                    {
                    x = readString(command);
                    }
                else 
                    {
                    x = readToken(command);
                    }
                insertAVL(a, newSTRING(x));
                continue;
                }
            else if(strcmp(x, "d") == 0) //delete
                {
                    if (stringPending(command)) 
                        {
                        x = readString(command);
                        }
                    else 
                        {
                        x = readToken(command);
                        }
                    deleteAVL(a, newSTRING(x));
                continue;
                }
            else if (strcmp(x, "f") == 0) //return frequency
                {
                if (stringPending(command)) 
                    {
                    x = readString(command);
                    }
                else 
                    {
                    x = readToken(command);
                    }
                int count = findAVLcount(a, newSTRING(x));
                printf("Frequency of %s: %d\n", x, count);
                continue;
                }
            else if (strcmp(x, "s") == 0) //display tree
                {   
                displayAVL(g, stdout);
                continue;
                }
            else if(strcmp(x, "r") == 0) //display stats
                {
                statisticsAVL(g, stdout);
                continue;
                }
            }
        fclose(command);
        }
    }

void
Fatal(char *fmt, ...)
    {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
    }


static int
processOptions(int argc, char **argv)
    {
    int argIndex;
    int argUsed;
    int separateArg;
    //char *arg;

    argIndex = 1;

    while (argIndex < argc && *argv[argIndex] == '-')
        {
        /* check if stdin, represented by "-" is an argument */
        /* if so, the end of options has been reached */
        if (argv[argIndex][1] == '\0') return argIndex;

        separateArg = 0;
        argUsed = 0;

        switch (argv[argIndex][1])
            {
            case 'v': //exit program
                verbose = 1;
                break;
            case 'g': //gst tree
                treeType = 1;
                break;
            case 'r': //avl tree (default)
                treeType = 0;
                break;
            default:
                treeType = 0;
                break;
            }

        if (separateArg && argUsed)
            ++argIndex;

        ++argIndex;
        }

    return argIndex;
    }

char *cleanString(char *x) 
    {
    char *orig = x;
    char *cleaned = x;
    
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

    // if (*orig == ' ') { *cleaned++; } //remove front whitespace
    // if (/*end of string*/) { *cleaned-- = 0; } //remove back whitespace
    return x;
    }
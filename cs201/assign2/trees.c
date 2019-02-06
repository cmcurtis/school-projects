#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "scanner.h"
#include "string.h"
#include "gst.h"
#include "avl.h"


/* options */
int verbose = 0;
int treeType = 0;

static int processOptions(int,char **);
static void trim(char *str);
static char *cleanString(char *);
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
        char *x = 0;
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
            //  printf("cleaned x: \"%s\"\n", x);
            if (strcmp(x, "") != 0)
                {
                insertGST(g, newSTRING(x));
                }
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

        if (stringPending(command)) 
            {
            x = readString(command);
            }
        else 
            {
            x = readToken(command);
            }
        while(!feof(command))
            {
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
                cleanString(x);
                if (strcmp(x, "") != 0)
                    {
                    insertGST(g, newSTRING(x));
                    }
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
                    cleanString(x);
                    if (strcmp(x, "") != 0)
                        {
                        void *val = deleteGST(g, newSTRING(x));
                        if (val == 0 && strcmp(x, " ") != 0)
                            {
                            printf("Value %s not found.\n", x);
                            }
                        }
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
                cleanString(x);
                if (strcmp(x, "") != 0)
                    {
                    int count = findGSTcount(g, newSTRING(x));
                    printf("Frequency of %s: %d\n", x, count);
                    }
                }
            else if (strcmp(x, "s") == 0) //display tree
                {   
                displayGST(g, stdout);
                }
            else if(strcmp(x, "r") == 0) //display stats
                {
                statisticsGST(g, stdout);
                }
            
            if (stringPending(command)) 
                {
                x = readString(command);
                }
            else 
                {
                x = readToken(command);
                }
            }
        fclose(command);
        }

    else //avl
        {
        AVL *a = newAVL(displaySTRING, compareSTRING, freeSTRING);
        char *x = 0;
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
            if (strcmp(x, "") != 0)
                {
                insertAVL(a, newSTRING(x));
                }
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

        if (stringPending(command)) 
            {
            x = readString(command);
            }
        else 
            {
            x = readToken(command);
            }
        while(!feof(command))
            {
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
                cleanString(x);
                if (strcmp(x, "") != 0)
                    {
                    insertAVL(a, newSTRING(x));
                    }
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
                    cleanString(x);
                    if (strcmp(x, "") != 0)
                        {
                        void *val = deleteAVL(a, newSTRING(x));
                        if (val == 0)
                            {
                            printf("Value %s not found.\n", x);
                            }
                        }
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
                cleanString(x);
                if (strcmp(x, "") != 0)
                    {
                    int count = findAVLcount(a, newSTRING(x));
                    printf("Frequency of %s: %d\n", x, count);
                    } 
                }
            else if (strcmp(x, "s") == 0) //display tree
                {   
                displayAVL(a, stdout);
                }
            else if(strcmp(x, "r") == 0) //display stats
                {
                statisticsAVL(a, stdout);
                }
            //read next string    
            if (stringPending(command)) 
                {
                x = readString(command);
                }
            else 
                {
                x = readToken(command);
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
    //trim(x);
    //printf("x: \"%s\"\n", x);
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
            if (strcmp(orig+1, "\0") == 0) { *cleaned++ = 0; }
            else { *cleaned++ = ' '; }
            }
        else if (isalpha((unsigned char)*orig) || *orig == 0) 
            {
            *cleaned++ = tolower((unsigned char)*orig);
            }
        } while(*orig++ != 0);
    //printf("new x: \"%s\"\n", x);
    trim(x);
    //printf("trimmed x: \"%s\"\n", x);
    return x;
    }

void trim(char * str)
{
    int i, j;

    i = 0;
    while(str[i] == ' ')
        {
        i++;
        }
        
    if(i != 0)
        {
        j = 0;
        while(str[j + i] != '\0')
            {
            str[j] = str[j + i];
            j++;
            }
        str[j] = '\0'; 
        }

    j = 0;
    i = -1;
    while(str[j] != '\0')
        {
        if(str[j] != ' ')
            {
            i = j;
            }
        j++;
        }
    str[i + 1] = '\0';
}
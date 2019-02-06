#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#include "scanner.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "heap.h"

/* options */
int verbose = 0;
int type = 0;
int order = 0;

static int processOptions(int,char **);
void Fatal(char *,...);

int
main(int argc,char **argv)
    {
    //int argIndex;

    if (argc == 1) Fatal("%d arguments!\n",argc-1);

    processOptions(argc,argv);

    FILE *f;
    f = fopen(argv[argc-1], "r");

    if (verbose) 
        {
        printf("Written by Caley Curtis\n");
        printf("My heapsort works in n log n time because its reads in values in constant time, inserts them into a heap in linear time and removes the extreme value in logartithmic time.\n");
        return 0;   
        }
    HEAP *h = 0;
    if (!order) //default order
        {
        if (type == 0) //integers
            {
            h = newHEAP(displayINTEGER, compareINTEGER, freeINTEGER);
            int x;
            x = readInt(f);
            while (!feof(f))
                {
                insertHEAP(h, newINTEGER(x));
                x = readInt(f);
                }
            fclose(f);
            }
        else if (type == 1) //reals
            {
            h = newHEAP(displayREAL, compareREAL, freeREAL);
            double x;
            x = readReal(f);
            while (!feof(f))
                {
                insertHEAP(h, newREAL(x));
                x = readReal(f);
                }
            fclose(f);
            }
        else //strings or tokens
            {
            h = newHEAP(displaySTRING, compareSTRING, freeSTRING);
            char *x;
            if (stringPending(f)) 
                {
                x = readString(f);
                }
            else 
                {
                x = readToken(f);
                }
            while (!feof(f))
                {
                insertHEAP(h, newSTRING(x));
                if (stringPending(f)) 
                    {
                    x = readString(f);
                    }
                else 
                    {
                    x = readToken(f);
                    }
                }
            fclose(f);
            }
        }
    else  //decreasing order
        {
        if (type == 0) //integers
            {
            h = newHEAP(displayINTEGER, rcompareINTEGER, freeINTEGER);
            int x;
            x = readInt(f);
            while (!feof(f))
                {
                insertHEAP(h, newINTEGER(x));
                x = readInt(f);
                }
            fclose(f);
            }
        else if (type == 1) //reals
            {
            h = newHEAP(displayREAL, rcompareREAL, freeREAL);
            double x;
            x = readReal(f);
            while (!feof(f))
                {
                insertHEAP(h, newREAL(x));
                x = readReal(f);
                }
            fclose(f);
            }
        else //strings or tokens
            {
            h = newHEAP(displaySTRING, rcompareSTRING, freeSTRING);
            char *x;
            if (stringPending(f)) 
                {
                x = readString(f);
                }
            else 
                {
                x = readToken(f);
                }
            while (!feof(f))
                {
                insertHEAP(h, newSTRING(x));
                if (stringPending(f)) 
                    {
                    x = readString(f);
                    }
                else 
                    {
                    x = readToken(f);
                    }
                }
            fclose(f);
            }
        }
    buildHEAP(h);
    while(sizeHEAP(h) != 0)
        {
        void *val;
        val = extractHEAP(h);
        if (type == 0) { displayINTEGER(val, stdout); }
        else if (type == 1) { displayREAL(val, stdout); }
        else { displaySTRING(val, stdout); }
        if (sizeHEAP(h) != 0) { printf(" "); } 
        }
    printf("\n");
    return 0;
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

        // if (argv[argIndex][2] == '\0')
        //     {
        //     arg = argv[argIndex+1];
        //     separateArg = 1;
        //     }
        // else
        //     arg = argv[argIndex]+2;

        switch (argv[argIndex][1])
            {
            case 'v': //exit program
                verbose = 1;
                break;
            case 'i': //sort a file of integers (default)
                type = 0;
                break;
            case 'r': //sort a file of real numbers
                type = 1;
                break;
            case 's': //sort a file of tokens or quoted strings
                type = 2;
                break;
            case 'I': //sort in increasing order (default)
                order = 0;
                break;
            case 'D': //sort in decreasing order
                order = 1;
                break;    
            default:
                Fatal("option %s not understood\n",argv[argIndex]);
            }

        if (separateArg && argUsed)
            ++argIndex;

        ++argIndex;
        }

    return argIndex;
    }
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "scanner.h"
#include "vertex.h"
#include "edge.h"
#include "avl.h"
#include "integer.h"

/* options */
int verbose = 0;

static int processOptions(int,char **);
void Fatal(char *,...);

int
main(int argc,char **argv)
    {

    if (argc == 1) Fatal("%d arguments!\n",argc-1);

    processOptions(argc,argv);

    FILE *graph;
    graph = fopen(argv[argc - 1], "r");

    if (verbose) 
        {
        printf("Written by Caley Curtis\n");
        return 0;   
        }

    AVL* vertexTree = newAVL(displayVERTEX, compareVERTEX, freeVERTEX);
    AVL* edgeTree = newAVL(displayEDGE, compareEDGE, freeEDGE);
    int n1 = 0;
    int n2 = 0;
    int weight = 0; 

    n1 = readInt(graph);
    n2 = readInt(graph);
    weight = readInt(graph);

    int firstVertex = n1;
    
    while(!feof(graph))
        {
        VERTEX *v1 = newVERTEX(n1);
        VERTEX *v2 = newVERTEX(n2);
        EDGE *w = newEDGE(n1, n2, weight);
        
        insertVERTEXneighbor(v1, v2);
        insertVERTEXneighbor(v1, v2);

        VERTEX *find1 = findAVL(vertexTree, v1);
        VERTEX *find2 = findAVL(vertexTree, v2);
        EDGE *findW = findAVL(edgeTree, w);

        if(find1 == NULL) 
            {
            insertAVL(vertexTree, v1);
            if(find2 == NULL) { insertAVL(vertexTree, v2); }
            else 
                {
                insertVERTEXneighbor(find2, v1);
                insertVERTEXweight(find2, weight); 
                }
            }
        else
            {
            insertVERTEXneighbor(find1, v2);
            insertVERTEXweight(find1, weight);
            if(find2 == NULL) { insertAVL(vertexTree, v2); }
            else 
                {
                insertVERTEXneighbor(find2, find1);
                insertVERTEXweight(find2, weight);
                }
            }

        if (findW == NULL)
            {
            insertAVL(edgeTree, w);
            }
        else { freeEDGE(w); }

        n1 = readInt(graph);
        n2 = readInt(graph);
        weight = readInt(graph);
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
            default:
                verbose = 0;
                break;
            }

        if (separateArg && argUsed)
            ++argIndex;

        ++argIndex;
        }

    return argIndex;
    }
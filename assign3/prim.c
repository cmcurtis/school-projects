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
#include "binomial.h"
#include "queue.h"

/* options */
int verbose = 0;

static int processOptions(int,char **);
void Fatal(char *,...); 

//static void *PRIMS(BINOMIAL* b, VERTEX* s);

static void update(void *w, void *o)
    {
    VERTEX *v = w;
    setVERTEXowner(v, o);
    }

static int compareV(void *a,void *b)
    {
    VERTEX *x = a;
    VERTEX *y = b;

    if (getVERTEXkey(x) > getVERTEXkey(y))
        return 1;
    else 
        return -1;
    }

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
    BINOMIAL* heap = newBINOMIAL(displayVERTEX, compareVERTEX, update, freeVERTEX);

    int n1 = 0;
    int n2 = 0;
    int weight = 0; 
    char *separator = 0; 

    n1 = readInt(graph);
    n2 = readInt(graph);
    weight = readInt(graph);
    separator = readToken(graph);
    
    int firstVertex = n1;

    //READ IN GRAPH
    while(!feof(graph))
        {
        EDGE *w = 0;
        if(n1 > n2) { w = newEDGE(n1, n2, weight); }
        else { w = newEDGE(n2, n1, weight); }
        VERTEX *v1 = newVERTEX(n1);
        if(n1 == firstVertex) { setVERTEXkey(v1, 0); }
        
        VERTEX *v2 = newVERTEX(n2);

        VERTEX *find1 = findAVL(vertexTree, v1);
        VERTEX *find2 = findAVL(vertexTree, v2);
        EDGE *findW = findAVL(edgeTree, w);

        if (n1 == n2 || findW != NULL) 
            {
            n1 = readInt(graph);
            n2 = readInt(graph);
            weight = readInt(graph);
            separator = readToken(graph);
            continue;
            }
        else
            {
            if(find1 == NULL) 
                {
                insertAVL(vertexTree, v1);
                insertVERTEXneighbor(v1, v2);
                insertVERTEXweight(v1, weight);
                setVERTEXowner(v1, insertBINOMIAL(heap, v1));
                }
            else 
                {
                insertVERTEXneighbor(find1, v2);
                insertVERTEXweight(find1, weight);
                }
            if(find2 == NULL) 
                {
                insertAVL(vertexTree, v2);
                insertVERTEXneighbor(v2, v1);
                insertVERTEXweight(v2, weight);
                setVERTEXowner(v2, insertBINOMIAL(heap, v2));
                }
            else 
                {
                insertVERTEXneighbor(find2, v1);
                insertVERTEXweight(find2, weight); 
                }
            if (findW == NULL)
                {
                insertAVL(edgeTree, w);
                }
            n1 = readInt(graph);
            n2 = readInt(graph);
            weight = readInt(graph);
            separator = readToken(graph);
            }
        }
    free(separator);

    VERTEX *start = peekBINOMIAL(heap);
    //RUN PRIMS
    VERTEX *u = 0;
    VERTEX *v = 0;
    INTEGER *w = 0;
    VERTEX *p = 0;
    DLL *n = 0;
    DLL *m = 0;
    

    displayBINOMIALdebug(heap, stdout);
    while(sizeBINOMIAL(heap) != 0)
        {
        u = extractBINOMIAL(heap);
        p = getVERTEXpred(u);
        
        if (p != NULL) { insertVERTEXsuccessor(p, u); }
    
        setVERTEXflag(u, 1);
        displayDLL(getVERTEXneighbors(u), stdout);
        n = getVERTEXneighbors(u);
        m = getVERTEXweights(u);
        firstDLL(n);
        firstDLL(m);
        while(moreDLL(n))
            {
            v = currentDLL(n);
            w = currentDLL(m);
            if(getVERTEXflag(v) == 0 && compareINTEGER(w, newINTEGER(getVERTEXkey(v))) > 0)
                {
                // printf("VERTEX TO BE UPDATED: ");
                // displayVERTEX(v, stdout);
                // printf("::");
                setVERTEXpred(v, u);
                // printf("KEY TO BE UPDATED TO: ");
                // displayINTEGER(w, stdout);
                // printf("\n");
                //printf("::");
                setVERTEXkey(v, getINTEGER(w));
                decreaseKeyBINOMIAL(heap, getVERTEXowner(v), w);
                // printf("NEW KEY : %d \n", getVERTEXkey(v));
                }
            nextDLL(n);
            nextDLL(m);
            }
        
        }

    displayDLL(getVERTEXsuccessors(start), stdout);
    //PRINT MST
    BINOMIAL *printer = newBINOMIAL(displayVERTEX, compareV, 0, freeVERTEX);

    QUEUE *Q1 = newQUEUE(0,0);
    QUEUE *Q2 = newQUEUE(0,0);
    enqueue(Q1, start);
    int count = 0;
    int first = 0;
    while(sizeQUEUE(Q1) != 0 || sizeQUEUE(Q2) != 0)
        {
        while(sizeQUEUE(Q1) != 0)
            {
            if (first == 0) { printf("%d: ", count); }
            VERTEX *current = peekQUEUE(Q1);
            if(getVERTEXsuccessors(current) != 0) 
                {
                firstDLL(getVERTEXsuccessors(current));
                VERTEX *temp1 = 0;
                while(moreDLL(getVERTEXsuccessors(current)) != 0)
                    {   
                    temp1 = currentDLL(getVERTEXsuccessors(current));
                    insertBINOMIAL(printer, temp1);
                    nextDLL(getVERTEXsuccessors(current));
                    }
                while(sizeBINOMIAL(printer) != 0) 
                    {
                    VERTEX *ordered1 = extractBINOMIAL(printer);
                    enqueue(Q2, ordered1);
                    }
                }
            displayVERTEX(current, stdout);
            if (sizeQUEUE(Q1) > 1) { printf(" "); }
            dequeue(Q1);
            first++;
            }
        printf("\n");
        count++;
        first = 0;
        if (sizeQUEUE(Q2) == 0) { break; }
        while(sizeQUEUE(Q2) != 0)
            {
            if (first == 0) { printf("%d: ", count); }
            VERTEX *second = peekQUEUE(Q2); 
            if(getVERTEXsuccessors(second) != 0) 
                {
                firstDLL(getVERTEXsuccessors(second));
                VERTEX *temp2 = 0;
                while(moreDLL(getVERTEXsuccessors(second)) != 0)
                    {   
                    temp2 = currentDLL(getVERTEXsuccessors(second));
                    insertBINOMIAL(printer, temp2);
                    nextDLL(getVERTEXsuccessors(second));
                    }
                while(sizeBINOMIAL(printer) != 0) 
                    {
                    VERTEX *temp2 = extractBINOMIAL(printer);
                    enqueue(Q1, temp2);
                    }
                }
            displayVERTEX(second, stdout);
            if (sizeQUEUE(Q2) > 1) { printf(" "); }
            
            dequeue(Q2);
            first++;
            }
        first = 0;
        printf("\n");
        count++;
        }
    freeQUEUE(Q1);
    freeQUEUE(Q2);
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

// void *PRIMS(BINOMIAL* b, VERTEX* s)
//     {
//     setVERTEXkey(s, 0);

//     }
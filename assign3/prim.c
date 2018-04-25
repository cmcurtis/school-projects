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

static BINOMIAL* readGraph(FILE *fp);
static void PRIMS(BINOMIAL* b);
static void printMST(VERTEX *s);

static void update(void *w, void *o)
    {
    VERTEX *v = w;
    setVERTEXowner(v, o);
    }

static int compareV(void *a,void *b)
    {
    VERTEX *x = a;
    VERTEX *y = b;

    if (getVERTEXnumber(x) > getVERTEXnumber(y))
        return 1;
    else 
        return -1;
    }

static void printVertex(VERTEX* v)
    {
    displayVERTEX(v, stdout);
    if (getVERTEXpred(v) != NULL)
        {
        printf("(");
        displayVERTEX(getVERTEXpred(v), stdout);
        printf(")%d", getVERTEXkey(v));
        }
    }

int
main(int argc,char **argv)
    {

    if (argc == 1) Fatal("%d arguments!\n",argc-1);

    processOptions(argc,argv);

    if (verbose) 
        {
        printf("Written by Caley Curtis\n");
        return 0;   
        }

    FILE *graph;
    graph = fopen(argv[argc - 1], "r");

    BINOMIAL *heap = readGraph(graph);
    fclose(graph);

    //displayBINOMIALdebug(heap, stdout);

    VERTEX *start = peekBINOMIAL(heap);
    
    //RUN PRIMS
    PRIMS(heap);

    //displayDLL(getVERTEXsuccessors(start), stdout);
    
    //PRINT MST
    printMST(start);
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


BINOMIAL* readGraph(FILE *fp)
    {
    AVL* vertexTree = newAVL(displayVERTEX, compareVERTEX, freeVERTEX);
    AVL* edgeTree = newAVL(displayEDGE, compareEDGE, freeEDGE);
    BINOMIAL* heap = newBINOMIAL(displayVERTEX, compareVERTEX, update, freeVERTEX);

    int n1 = 0;
    int n2 = 0;
    int weight = 0; 
    char *separator = 0; 

    n1 = readInt(fp);
    n2 = readInt(fp);
    weight = readInt(fp);
    separator = readToken(fp);
    
    int firstVertex = n1;

    while(!feof(fp))
        {
        EDGE *w = newEDGE(n1, n2, weight);
        VERTEX *v1 = newVERTEX(n1);
        VERTEX *v2 = newVERTEX(n2);

        if(n1 == firstVertex) { setVERTEXkey(v1, 0); }

        VERTEX *find1 = findAVL(vertexTree, v1);
        VERTEX *find2 = findAVL(vertexTree, v2);
        EDGE *findW = findAVL(edgeTree, w);

        if (find1 != NULL && find2 != NULL && findW == NULL) //v1 & v2 exist but not connected 
            {
            insertVERTEXneighbor(find1, find2);
            insertVERTEXweight(find1, weight);
            insertVERTEXneighbor(find2, find1);
            insertVERTEXweight(find2, weight);

            insertAVL(edgeTree, w);
            }
        if (find1 != NULL && find2 == NULL) //v1 exists - v2 does not
            {
            insertVERTEXneighbor(find1, v2);
            insertVERTEXweight(find1, weight);
            insertVERTEXneighbor(v2, find1);
            insertVERTEXweight(v2, weight);

            insertAVL(edgeTree, w);
            insertAVL(vertexTree, v2);

            setVERTEXowner(v2, insertBINOMIAL(heap, v2));
            }
        else if (find1 == NULL && find2 != NULL) //v2 exist - v1 does not
            {
            insertVERTEXneighbor(find2, v1);
            insertVERTEXweight(find2, weight);
            insertVERTEXneighbor(v1, find2);
            insertVERTEXweight(v1, weight);

            insertAVL(edgeTree, w);
            insertAVL(vertexTree, v1);

            setVERTEXowner(v1, insertBINOMIAL(heap, v1));
            }
        else if(find1 == NULL && find2 == NULL)//are not in tree
            {
            insertVERTEXneighbor(v1, v2);
            insertVERTEXweight(v1, weight);
            insertVERTEXneighbor(v2, v1);
            insertVERTEXweight(v2, weight);

            insertAVL(edgeTree, w);
            insertAVL(vertexTree, v2);
            insertAVL(vertexTree, v1);

            setVERTEXowner(v1, insertBINOMIAL(heap, v1));
            setVERTEXowner(v2, insertBINOMIAL(heap, v2));
            }

            n1 = readInt(fp);
            n2 = readInt(fp);
            weight = readInt(fp);
            separator = readToken(fp);
        }
    free(separator);
    return heap;
    }

void PRIMS(BINOMIAL* heap)
    {
    VERTEX *u = 0;
    VERTEX *v = 0;
    INTEGER *w = 0;
    VERTEX *p = 0;
    DLL *n = 0;
    DLL *m = 0;
    
    while(sizeBINOMIAL(heap) != 0)
        {
        // displayBINOMIAL(heap, stdout);
        // displayBINOMIALdebug(heap, stdout);

        u = extractBINOMIAL(heap);
        p = getVERTEXpred(u);
        
    
        // DEBUGGING
        // printf("EXTRACTED VAL:");
        // displayVERTEX(u, stdout);
        // printf("\n");
        
        // getchar();
        //DEBUGGING

        if (p != NULL) { insertVERTEXsuccessor(p, u); }
    
        setVERTEXflag(u, 1);
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
                
                setVERTEXkey(v, getINTEGER(w));
                decreaseKeyBINOMIAL(heap, getVERTEXowner(v), v);
                
                // printf("NEW KEY : %d \n", getVERTEXkey(v));
                }
            nextDLL(n);
            nextDLL(m);
            }
        }
    }

void printMST(VERTEX *start)
    {
    BINOMIAL *printer = newBINOMIAL(displayVERTEX, compareV, 0, freeVERTEX);

    QUEUE *Q1 = newQUEUE(0,0);
    QUEUE *Q2 = newQUEUE(0,0);
    enqueue(Q1, start);
    int count = 0;
    int weight = 0;
    while(sizeQUEUE(Q1) != 0)
        {
        printf("%d: ", count);
        while(sizeQUEUE(Q1) != 0)
            {
            VERTEX *current = dequeue(Q1);
            firstDLL(getVERTEXsuccessors(current));
            VERTEX *temp1 = 0;
            while(moreDLL(getVERTEXsuccessors(current)) != 0)
                {   
                temp1 = currentDLL(getVERTEXsuccessors(current));
                insertBINOMIAL(printer, temp1);
                //enqueue(Q2, temp1);
                nextDLL(getVERTEXsuccessors(current));
                }
            while(sizeBINOMIAL(printer) != 0) 
                {
                temp1 = extractBINOMIAL(printer);
                enqueue(Q2, temp1);
                weight += getVERTEXkey(temp1);
                }
            printVertex(current);
            if (sizeQUEUE(Q1) > 0) { printf(" "); }
            }
        printf("\n");
        //getchar();
        count++;
        QUEUE *tempQ = Q1;
        Q1 = Q2;
        Q2 = tempQ;
        }
    printf("weight: %d\n", weight);
    freeQUEUE(Q1);
    freeQUEUE(Q2);
    }
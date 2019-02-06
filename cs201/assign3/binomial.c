#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "dll.h"
#include "queue.h"
#include "binomial.h"

static void bDisplay(void *b, FILE *fp);
static void bFree(void *b);

typedef struct bnode
    {
    void *value;
    void *owner;
    struct bnode *parent;
    DLL *childList;
    void (*display)();
    void (*free)();
    }bNODE;

bNODE *newBNODE(void *v, void (*d)(void *,FILE *), void (*f)(void *))
    {
    bNODE *n = malloc(sizeof(bNODE));

    n->value = v;
    n->owner = 0;
    n->parent = 0;
    n->childList = newDLL(bDisplay, bFree);
    n->display = d;
    n->free = f;
    return n;
    }

void bDisplay(void *b, FILE *fp)
    {
    bNODE *x = b;
    x->display(x->value, fp);
    }

void bFree(void *b)
    {
    bNODE *x = b;
    if (x->free != 0) { x->free(x->value); }
    freeDLL(x->childList);
    free(x);
    }

static bNODE* combine(BINOMIAL *b, bNODE *x, bNODE *y);
static void consolidate(BINOMIAL *b);
static void updateConsolidationArray(BINOMIAL *b, bNODE **D, bNODE *n);
static bNODE* bubbleUp(BINOMIAL *b, bNODE *n);

struct binomial
    {
    DLL *rootList;
    int size;
    bNODE *extremeVal;
    void (*display)(void*, FILE*);
    int (*compare)(void*, void*);
    void (*update)(void*, void*);
    void (*free)(void*);
    };

BINOMIAL* newBINOMIAL(void (*d)(void *,FILE *), int (*c)(void *,void *), void (*u)(void *,void *), void (*f)(void *))
    {
    BINOMIAL *b = malloc(sizeof(BINOMIAL));

    b->rootList = newDLL(bDisplay, bFree); 
    b->size = 0;
    b->extremeVal = NULL;
    b->display = d;
    b->compare = c;
    b->update = u;
    b->free = f;

    return b;
    }

void *insertBINOMIAL(BINOMIAL *b, void *value)
    {
    bNODE *n = newBNODE(value, b->display, b->free); 
    n->parent = n;
    n->owner = insertDLL(b->rootList, 0, n); // insert n into the rootlist of b (via linked-list insert)
    b->size = sizeBINOMIAL(b) + 1;
    consolidate(b);
    return n;
    }

int sizeBINOMIAL(BINOMIAL *b)
    {
    return b->size;
    }

void unionBINOMIAL(BINOMIAL *r, BINOMIAL *d)
    {
    unionDLL(r->rootList, d->rootList);
    r->size += d->size;
    removeDLLall(d->rootList);
    d->size = 0;
    d->extremeVal = 0;
    consolidate(r);
    }

void deleteBINOMIAL(BINOMIAL *b, void *n)
    {
    decreaseKeyBINOMIAL(b, n, 0);
    void *temp = extractBINOMIAL(b);
    bFree(temp);
    }

void decreaseKeyBINOMIAL(BINOMIAL *b, void *n, void *value)
    {
    bNODE *m = n;
    m->value = value;
    bNODE *temp = bubbleUp(b, m);
    // if (b->extremeVal != NULL)
    //     {
    //     // printf("decreasekey comparing ");
    //     // b->display(b->extremeVal->value, stdout);
    //     // printf(" with ");
    //     // b->display(temp->value, stdout);
    //     // printf("\n");
    //     }
    if (b->compare(b->extremeVal->value, temp->value) >= 0) 
        {
        // printf("decrease key setting extreme Value to: ");
        // b->display(temp->value, stdout);
        // printf("\n");
        b->extremeVal = temp; 
        }
    }

void *peekBINOMIAL(BINOMIAL *b)
    {
    return b->extremeVal->value;
    }

void *extractBINOMIAL(BINOMIAL *b)
    {
    assert(b->extremeVal != NULL);
    
    bNODE *y = b->extremeVal;
    bNODE *deleted = removeDLLnode(b->rootList, y->owner); 
    void *val = deleted->value;

    firstDLL(y->childList);
    bNODE *temp = 0;
    while(moreDLL(y->childList) != 0)
        {
        temp = currentDLL(y->childList);
        temp->parent = temp;
        nextDLL(y->childList);
        }
    unionDLL(y->childList, b->rootList);
    unionDLL(b->rootList, y->childList);
    consolidate(b);
    b->size -= 1;
    free(deleted->childList);
    free(deleted);
    return val;
    }

void statisticsBINOMIAL(BINOMIAL *b,FILE *fp)
    {
    fprintf(fp, "size: %d\n", b->size);
    fprintf(fp, "rootlist size: %d\n", sizeDLL(b->rootList));
    if (b->size != 0) 
        {
        fprintf(fp, "extreme: ");
        b->display(b->extremeVal->value, stdout);
        fprintf(fp, "\n");
        }
    }

void displayBINOMIAL(BINOMIAL *b,FILE *fp)
    {
    assert(b != 0);
    fprintf(fp, "rootlist:");
    int count = 0;
    firstDLL(b->rootList);
    bNODE *temp = 0; 
    while (moreDLL(b->rootList) == 1)
        {
        temp = currentDLL(b->rootList); 
        if (count == sizeDLL(temp->childList))  
            {
            fprintf(fp, " "); 
            temp->display(temp->value, fp);
            if (temp == b->extremeVal && temp != NULL) { fprintf(fp, "*"); }
            nextDLL(b->rootList);                                    
            }
        else 
            {
            fprintf(fp, " NULL"); 
            }
        count++;
        }
    fprintf(fp, "\n");
    }

void displayBINOMIALdebug(BINOMIAL *b,FILE *fp)
    {
    displayDLL(b->rootList, fp);
    //print childLists if they exist;
    firstDLL(b->rootList);
    bNODE *root = 0;
    QUEUE *Q1 = newQUEUE(bDisplay,0);
    QUEUE *Q2 = newQUEUE(bDisplay,0);
    
    while(moreDLL(b->rootList) != 0)
        {
        root = currentDLL(b->rootList);
        enqueue(Q1, root);
        nextDLL(b->rootList);
        }
    fprintf(fp, "\n");
    while(sizeQUEUE(Q1) != 0 || sizeQUEUE(Q2) != 0)
        {
        while(sizeQUEUE(Q1) != 0)
            {
            bNODE *current = peekQUEUE(Q1);
            
            if(current->childList != 0) 
                {
                firstDLL(current->childList);
                bNODE *temp1 = 0;
                while(moreDLL(current->childList) != 0)
                    {   
                    temp1 = currentDLL(current->childList);
                    enqueue(Q2, temp1);
                    nextDLL(current->childList);
                    }
                }
            if (sizeDLL(current->childList) != 0) { displayDLL(current->childList, fp); }
            dequeue(Q1);
            }
        if (sizeQUEUE(Q2) != 0) { fprintf(fp, "\n"); }
        if (sizeQUEUE(Q2) == 0) { break; }
        while(sizeQUEUE(Q2) != 0)
            {
            bNODE *second = peekQUEUE(Q2); 
            if(second->childList != 0) 
                {
                firstDLL(second->childList);
                bNODE *temp2 = 0;
                while(moreDLL(second->childList))
                    {
                    temp2 = currentDLL(second->childList);
                    enqueue(Q1, temp2);
                    nextDLL(second->childList);
                    }
                }
            if (sizeDLL(second->childList) != 0) { displayDLL(second->childList, fp); }
            dequeue(Q2);
            }
        if (sizeQUEUE(Q1) != 0) { fprintf(fp, "\n"); }
        }
    freeQUEUE(Q1);
    freeQUEUE(Q2);
    }

void freeBINOMIAL(BINOMIAL *b)
    {
    freeDLL(b->rootList);
    free(b);
    }


// The combine routine takes two subheaps and makes the subheap, whose root is less extreme, a child of the other: 
bNODE* combine(BINOMIAL *b, bNODE *x, bNODE *y) //returns binomial heap node
    {
    if (b->compare(x->value, y->value) < 0) 
        {
        y->owner = insertDLL(x->childList, sizeDLL(x->childList), y);
        y->parent = x;
        return x;
        }
    else
        {
        x->owner = insertDLL(y->childList, sizeDLL(y->childList), x);
        x->parent = y;
        return y;
        }
    }

void consolidate(BINOMIAL *b)
    {
    int size = (log(sizeBINOMIAL(b))/log(2)) + 1;
    bNODE **D = malloc(size*sizeof(bNODE));
    for (int i = 0; i < size; i++) { D[i] = NULL; } //initialize array to null.

    int j = 0;
    bNODE *temp = NULL;
    while(sizeDLL(b->rootList) != 0)
        {
        firstDLL(b->rootList);
        temp = currentDLL(b->rootList);

        j = sizeDLL(temp->childList);
        if (D[j] != NULL) 
            {
            bNODE *combined = removeDLLnode(b->rootList, temp->owner);
            updateConsolidationArray(b, D, combined);
            }
        else { D[j] = removeDLLnode(b->rootList, temp->owner); }
        }
    
    b->extremeVal = NULL;

    for (int k = 0; k < size; ++k)
        {
        if (D[k] != NULL) 
            {
            D[k]->owner = insertDLL(b->rootList, sizeDLL(b->rootList), D[k]); 
            // if (b->extremeVal != NULL)
            //     {
            //     printf("comparing ");
            //     b->display(b->extremeVal->value, stdout);
            //     printf(" with ");
            //     b->display(D[k]->value, stdout);
            //     printf("\n");
            //     }
            if (b->extremeVal == NULL || b->compare(b->extremeVal->value, D[k]->value) > 0)
                {
                // printf("setting extreme Value to: ");
                // b->display(D[k]->value, stdout);
                // printf("\n");
                b->extremeVal = D[k];
                }
            }
        }
    free(D);
    }

void updateConsolidationArray(BINOMIAL *b, bNODE **D, bNODE *n)
    {
    int j = sizeDLL(n->childList);
    
    bNODE* temp = 0;
    while(D[j] != NULL) 
        {
        temp = combine(b, n, D[j]);
        D[j] = 0;
        j++;
        n = temp;
        }
    D[j] = n;
    }

bNODE* bubbleUp(BINOMIAL *b, bNODE *n)
    {
    bNODE* p = n->parent;
    if (n == p) return n;
    if (b->compare(n->value,p->value) >= 0) return n;
    if (b->update != 0) 
        {
        b->update(n->value,p);
        b->update(p->value,n);
        }
    void* temp = n->value;
    n->value = p->value;
    p->value = temp;
    return bubbleUp(b, p);
    }
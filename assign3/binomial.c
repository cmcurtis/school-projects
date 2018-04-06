#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "dll.h"
#include "binomial.h"
#include "queue.h"

typedef struct bnode
    {
    void *value;
    struct bnode *parent;
    DLL *childList;
    }bNODE;

bNODE *newBNODE(void *v, void (*d)(void *,FILE *), void (*f)(void *))
    {
    bNODE *n = malloc(sizeof(bNODE));

    n->value = v;
    n->parent = 0;
    n->childList = newDLL(d, f);

    return n;
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
    void (*display)();
    int (*compare)();
    void (*update)();
    void (*free)();
    };

BINOMIAL* newBINOMIAL(void (*d)(void *,FILE *), int (*c)(void *,void *), void (*u)(void *,void *), void (*f)(void *))
    {
    BINOMIAL *b = malloc(sizeof(BINOMIAL));

    b->rootList = newDLL(d, f); //?? DIFF DISPLAY?
    b->size = 0;
    b->extremeVal = 0;
    b->display = d;
    b->compare = c;
    b->update = u;
    b->free = f;

    return b;
    }

void *insertBINOMIAL(BINOMIAL *b, void *value)
    {
    bNODE *n = newBNODE(value, b->display, b->free); //set a variable n to a new node containing value v
    n->parent = n;
    insertDLL(b->rootList, 0, n); // insert n into the rootlist of b (via linked-list insert)
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
    free(temp);
    }

void decreaseKeyBINOMIAL(BINOMIAL *b, void *n, void *value)
    {
    bNODE *m = n;
    m->value = value;
    bNODE *temp = bubbleUp(b, m);
    if (b->compare(temp, b->extremeVal) >= 0) { b->extremeVal = temp; }
    }

void *peekBINOMIAL(BINOMIAL *b)
    {
    return b->extremeVal->value;
    }

void *extractBINOMIAL(BINOMIAL *b)
    {
    bNODE *y = b->extremeVal;
    void *deleted = removeDLLnode(b->rootList, y); 
    
    firstDLL(y->childList);
    bNODE *temp = currentDLL(y->childList);
    while(temp != 0)
        {
        temp->parent = temp;
        nextDLL(y->childList);
        temp = currentDLL(y->childList);
        }
    unionDLL(b->rootList, y->childList);
    consolidate(b);
    b->size -= 1;
    return deleted;
    }

void statisticsBINOMIAL(BINOMIAL *b,FILE *fp)
    {
    fprintf(fp, "size: %d\n", b->size);
    fprintf(fp, "rootlist size: %d\n", sizeDLL(b->rootList));
    if (b->size != 0) 
        {
        fprintf(fp, "extreme: ");
        b->display(b->extremeVal->value);
        fprintf(fp, "\n");
        }
    }

void displayBINOMIAL(BINOMIAL *b,FILE *fp)
    {
    assert(b != 0);
    fprintf(fp, "rootlist:");
    int count = 0;
    firstDLL(b->rootList);
    bNODE *temp = currentDLL(b->rootList);
    while (temp != 0)
        {
        if (count == sizeDLL(temp->childList))
            {
            fprintf(fp, " "); 
            b->display(temp, fp); 
            }
        else { fprintf(fp, " NULL"); }
        if (temp == b->extremeVal) { fprintf(fp, "*"); }
        count++;
        nextDLL(b->rootList);
        temp = currentDLL(b->rootList);
        }
    }

//The method displays the entire heap, using a level-order traversal of each subheap in turn. Suppose the values 0 
//through 12 were inserted, in order, into an empty heap. The display of that heap would look like: 
//     {{12,8,0}}
//     {{9,10}}{{1,2,4}}
//     {{11}}{{3}}{{5,6}}
//     {{7}}
// Note that the rootlist and all the child values are always ordered from low degree to high degree.
void displayBINOMIALdebug(BINOMIAL *b,FILE *fp)
    {
    displayDLL(b->rootList, fp);
    //print childLists if they exist;
    firstDLL(b->rootList);
    bNODE *root = currentDLL(b->rootList);
    QUEUE *Q1 = newQUEUE(0,0);
    QUEUE *Q2 = newQUEUE(0,0);
    
    while(root != 0)
        {
        enqueue(Q1, root);
        nextDLL(b->rootList);
        root = currentDLL(b->rootList);
        }
    
    while(sizeQUEUE(Q1) != 0 || sizeQUEUE(Q2) != 0)
        {
        while(sizeQUEUE(Q1) != 0)
            {
            bNODE *current = peekQUEUE(Q1);
            if(current->childList != 0) 
                {
                firstDLL(current->childList);
                bNODE *temp1 = currentDLL(current->childList);
                while(temp1 != 0)
                    {
                    enqueue(Q2, temp1);
                    nextDLL(current->childList);
                    temp1 = currentDLL(current->childList);
                    }
                }
            if (current->childList != 0) { displayDLL(current->childList, fp); }
            if (sizeQUEUE(Q1) > 1) { fprintf(fp, " "); }
            dequeue(Q1);
            }
        fprintf(fp, "\n");
        if (sizeQUEUE(Q2) == 0) { break; }
        while(sizeQUEUE(Q2) != 0)
            {
            bNODE *second = peekQUEUE(Q2); 
            if(second->childList != 0) 
                {
                firstDLL(second->childList);
                bNODE *temp2 = currentDLL(second->childList);
                while(temp2 != 0)
                    {
                    enqueue(Q1, temp2);
                    nextDLL(second->childList);
                    temp2 = currentDLL(second->childList);
                    }
                }
            if (second->childList != 0) { displayDLL(second->childList, fp); }
            if (sizeQUEUE(Q2) > 1) { fprintf(fp, " "); }
            dequeue(Q2);
            }
        fprintf(fp, "\n");
        }
    freeQUEUE(Q1);
    freeQUEUE(Q2);
    }

void freeBINOMIAL(BINOMIAL *b)
    {

    }




// The combine routine takes two subheaps and makes the subheap, whose root is less extreme, a child of the other: 
bNODE* combine(BINOMIAL *b, bNODE *x, bNODE *y) //returns binomial heap node
    {
    if (b->compare(x->value, y->value) >= 0)
        {
        insertDLL(x->childList, sizeDLL(x->childList), y);
        y->parent = x;
        return x;
        }
    else
        {
        insertDLL(y->childList, sizeDLL(y->childList), x);
        x->parent = y;
        return y;
        }
    }

void consolidate(BINOMIAL *b)
    {
    int size = (log(sizeBINOMIAL(b))/log(2)) + 1;
    bNODE **D = malloc(sizeof(bNODE)*size);
    int i;
    for (i = 0; i < size; i++) { D[i] = 0; }

    while (sizeDLL(b->rootList) != 0)
        {
        firstDLL(b->rootList);
        bNODE *n = currentDLL(b->rootList); //set a variable spot to the head node in b's root list
        if (n != 0) //remove spot from the root list (via linked-list remove)
            { 
            void *temp = removeDLLnode(b->rootList, n); 
            n = temp;
            }
        updateConsolidationArray(b, D, n);
        }

    b->extremeVal = 0;
    for (i = 0; i < size; ++i)
        {
        if (D[i] != 0)
            {
            insertDLL(b->rootList, 0, D[i]);
            if (b->compare(D[i], b->extremeVal) > 0) { b->extremeVal = D[i]; }
            }
        }
    free(D);
    }

void updateConsolidationArray(BINOMIAL *b, bNODE **D, bNODE *n)
    {
    int i = sizeDLL(n->childList);   // set a variable degree to the number of spot's children (using linked-list size)
    while (D[i] != 0)
        {
        n = combine(b, n, D[i]); // combine spot and D[degree], setting spot to the combined subheap
        D[i] = 0;
        i++;
        }
    D[i] = n;
    }

bNODE* bubbleUp(BINOMIAL *b, bNODE *n)
    {
    bNODE* p = n->parent;
    if (n == p) return n;
    if (b->compare(n->value,p->value) >= 0) return n;
    if (b->update != 0) b->update(n->value,p);
    if (b->update != 0) b->update(p->value,n);
    bNODE* temp = n->value;
    n->value = p->value;
    p->value = temp;
    return bubbleUp(b, p);
    }
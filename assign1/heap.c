#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bst.h"
#include "stack.h"
#include "heap.h"
#include "queue.h"

//helper function
static void heapify(HEAP *h, BSTNODE *n);
static void swapVal(BSTNODE *n, BSTNODE *r);

struct heap
    {
    BST *tree;
    STACK *stack;
    QUEUE *queue;
    int size;
    void (*display)();
    int (*compare)();
    void (*free)();
    };

HEAP *newHEAP(
    void (*d)(void *,FILE *d),    //display
    int (*c)(void *,void *),     //compare
    void (*f)(void *))           //free
    {
    HEAP *heap = malloc(sizeof(HEAP));
    assert(heap != 0);
    
    heap->tree = newBST(d, c, 0, f);
    setBSTsize(heap->tree, 1);
    heap->stack = newSTACK(0, 0);
    heap->queue = newQUEUE(0, 0);
    heap->size = 0;
    heap->display = d;
    heap->compare = c;
    heap->free = f;
    return heap;
    }
  
void insertHEAP(HEAP *h,void *value)
    {
    assert(h != 0);
    BSTNODE* inserted = newBSTNODE(value);

    if (getBSTroot(h->tree) == 0)
        {
        setBSTroot(h->tree, inserted);
        enqueue(h->queue, inserted);
        push(h->stack, inserted);
        h->size++;
        }
    else   
        {
        BSTNODE *temp = 0;
        temp = peekQUEUE(h->queue);
        if (getBSTNODEleft(temp) == 0 && getBSTNODEright(temp) == 0)
            {
            setBSTNODEleft(temp, inserted);
            setBSTNODEparent(inserted, temp);
            enqueue(h->queue, inserted);
            push(h->stack, inserted);
            int v = sizeBST(h->tree);
            setBSTsize(h->tree, v + 1);
            h->size++;
            }
        else if(getBSTNODEleft(temp) != 0 && getBSTNODEright(temp) == 0)
            {
            setBSTNODEright(temp, inserted);
            setBSTNODEparent(inserted, temp);
            enqueue(h->queue, inserted);
            push(h->stack, inserted);
            int v = sizeBST(h->tree);
            setBSTsize(h->tree, v + 1);
            h->size++;
            }
        else 
            {
            dequeue(h->queue);
            free(inserted);
            insertHEAP(h, value);
            }
        }
    }


void buildHEAP(HEAP *h)
    {
    STACK *oldStack = h->stack;
    STACK *newStack = newSTACK(0, 0);
    
    BSTNODE* temp = 0;

    while( sizeSTACK(oldStack) != 0)
        {
        temp = pop(oldStack);
        push(newStack, temp);
        if (getBSTNODEleft(temp) != 0 || getBSTNODEright(temp) != 0)
            {
            heapify(h, temp);
            }
        }
    while (sizeSTACK(newStack) != 0)
        {
        temp = pop(newStack);
        push(oldStack, temp);
        }
    
    freeSTACK(newStack);
    }

void *peekHEAP(HEAP *h)
    {
    return getBSTNODEvalue(getBSTroot(h->tree));
    }

//This method returns the value at the “root” of the heap, rebuilding the heap. It should run in logarithmic time. 
void *extractHEAP(HEAP *h)
    {
    assert(sizeHEAP(h) !=0);
    
    BSTNODE *temp = 0;
    temp = pop(h->stack);
    // h->display(getBSTNODEvalue(temp), stdout);
    // h->display(getBSTNODEvalue(getBSTroot(h->tree)), stdout);
    if (sizeHEAP(h) > 1 ) { swapVal(temp, getBSTroot(h->tree)); }
    
    void *val = getBSTNODEvalue(temp);
    pruneLeafBST(h->tree, temp);
    
    int v = sizeBST(h->tree);
    setBSTsize(h->tree, --v);
    h->size--;

    if (sizeHEAP(h) != 0) { heapify(h, getBSTroot(h->tree)); }

    free(temp);
    return val;
    }

//returns the number of values currently in the tree
int sizeHEAP(HEAP *h)
    {
    return h->size;
    }

//The method calls the display method of the underlying data structure.     
void displayHEAP(HEAP *h,FILE *fp)
    {
    displayBST(h->tree, fp);
    }


void displayHEAPdebug(HEAP *h, FILE *fp)
    {
    int heapSize = sizeHEAP(h);
    int bstSize = sizeBST(h->tree);
    fprintf(fp, "heap size: %d\n", heapSize);
    fprintf(fp, "bst size: %d\n", bstSize);
    displayBSTdebug(h->tree, fp);
    }


void freeHEAP(HEAP *h)
    {
    freeBST(h->tree);
    freeQUEUE(h->queue);
    freeSTACK(h->stack);
    free(h);
    }


void heapify(HEAP *h, BSTNODE *n) //Look into this
    {
    BSTNODE *left = getBSTNODEleft(n);
    BSTNODE *right = getBSTNODEright(n);
    BSTNODE *temp = n;

    if(!left) return;

    if (h->compare(getBSTNODEvalue(left), getBSTNODEvalue(n)) < 0) { temp = left; }

    if(right)
        {
        if (h->compare(getBSTNODEvalue(right), getBSTNODEvalue(temp)) < 0) { temp = right; }
        }
    
    if(temp != n)
        {
        void *tempVal = getBSTNODEvalue(n);
        setBSTNODEvalue(n, getBSTNODEvalue(temp));
        setBSTNODEvalue(temp, tempVal);
        heapify(h, temp);
        }
    }

    void swapVal(BSTNODE *n, BSTNODE *r)
        {
        void *val = 0;
        void *valTwo = 0;
        val = getBSTNODEvalue(n);
        valTwo = getBSTNODEvalue(r);

        setBSTNODEvalue(n, valTwo);
        setBSTNODEvalue(r, val);
        }
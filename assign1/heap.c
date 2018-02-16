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
        
        heap->tree = newBST(d, 0, 0, f);
        heap->stack = newSTACK(0, 0);
        heap->queue = newQUEUE(0, 0);
        heap->size = 0;
        heap->display = d;
        heap->compare = c;
        heap->free = f;
        return heap;
    }

//This method inserts a generic value into an un-heapified heap. No fixing up of the heap should occur.
// It should run in constant time.     
void insertHEAP(HEAP *h,void *value)
    {
        assert(h != 0);
        BSTNODE* inserted = newBSTNODE(value);

        if (getBSTroot(h->tree) == 0)
            {
            setBSTroot(h->tree, inserted);
            enqueue(h->queue, inserted);
            push(h->stack, inserted);
            int v = sizeBST(h->tree);
            setBSTsize(h->tree, v++);
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
                // int v = sizeBST(h->tree);
                // setBSTsize(h->tree, v++);
                h->size++;   
                }
            else if(getBSTNODEleft(temp) != 0 && getBSTNODEright(temp) == 0)
                {
                setBSTNODEright(temp, inserted);
                setBSTNODEparent(inserted, temp);
                enqueue(h->queue, inserted);
                push(h->stack, inserted);
                // int v = sizeBST(h->tree);
                // setBSTsize(h->tree, v++);
                h->size++;
                }
            else 
                {
                dequeue(h->queue);
                insertHEAP(h, value);
                }
            }

    }

// This method imparts heap ordering on the current heap. 
// Once buildHEAP has been called, no insertions to the heap should be made.  
void buildHEAP(HEAP *h)
    {
    BSTNODE *temp = getBSTNODEparent(pop(h->stack));
    while(temp != peekSTACK(h->stack)) { pop(h->stack); }
    for (int i = h->size/2 - 1; i > 0; i--)
        {
        heapify(h, temp);
        pop(h->stack);
        }
    }

void *peekHEAP(HEAP *h)
    {
    return getBSTroot(h->tree);
    }

//This method returns the value at the “root” of the heap, rebuilding the heap. It should run in logarithmic time. 
void *extractHEAP(HEAP *h)
    {
    BSTNODE *root = deleteBST(peekHEAP(h), getBSTNODEvalue(peekHEAP(h)));
    heapify(h, root);
    h->size--;
    return root;
    }

//This method returns the number of values currently in the tree. It should run in amortized constant time.
int sizeHEAP(HEAP *h)
    {
    return h->size;
    }

//The method calls the display method of the underlying data structure.     
void displayHEAP(HEAP *h,FILE *fp)
    {
    displayBST(peekHEAP(h), fp);
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


void heapify(HEAP *h, BSTNODE *n)
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
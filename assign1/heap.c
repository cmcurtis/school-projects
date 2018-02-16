#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bst.h"

struct heap
    {
    BST *tree;
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
        
        heap->tree = 0;
        heap->size = 0;
        heap->display = d;
        heap->compare = c;
        heap->free = f;
    }

//This method inserts a generic value into an un-heapified heap. No fixing up of the heap should occur.
// It should run in constant time.     
void insertHEAP(HEAP *h,void *value)
    {
        assert(h != 0);
        
    }

// This method imparts heap ordering on the current heap. 
// Once buildHEAP has been called, no insertions to the heap should be made.  
void buildHEAP(HEAP *h)
    {
        
    }

//This method returns the value at the “root” of the heap; the heap is unmodified. It should run in constant time.
extern void *peekHEAP(HEAP *h)
    {

    }

//This method returns the value at the “root” of the heap, rebuilding the heap. It should run in logarithmic time. 
extern void *extractHEAP(HEAP *h)
    {

    }

//This method returns the number of values currently in the tree. It should run in amortized constant time.
extern int  sizeHEAP(HEAP *h)
    {

    }

//The method calls the display method of the underlying data structure.     
extern void displayHEAP(HEAP *h,FILE *fp)
    {

    }

// This method should print the size of the heap, the size of the underlying data structure, and call the debug display 
// method of the underlying data structure. Example (for a heap built upon a BST): 
//     heap size: 1
//     bst size: 1
//     4
extern void displayHEAPdebug(HEAP *h)
    {

    }

//This method frees the heap, in part by freeing the underlying data structure.
extern void freeHEAP(HEAP *h)
    {

    }
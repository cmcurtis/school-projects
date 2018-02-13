#include <stdio.h>

typedef struct heap HEAP;

// The constructor is passed three functions, one that knows how to display the generic value stored in the heap, one that 
// can compare two generic values, and one that can free a generic value. The comparator function is used to maintain heap 
// ordering (either a min-heap or a max-heap). 
extern HEAP *newHEAP(
    void (*)(void *,FILE *),    //display
    int (*)(void *,void *),     //compare
    void (*)(void *))           //free
    {
        //The memory allocated shall not be zero. 
    }

//This method inserts a generic value into an un-heapified heap. No fixing up of the heap should occur.
// It should run in constant time.     
extern void insertHEAP(HEAP *h,void *value)
    {
        //The memory allocated shall not be zero. 
    }

//This method inserts a generic value into a heapified heap, rebuilding the heap. It should run in logarithmic time. 
extern void buildHEAP(HEAP *h)
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
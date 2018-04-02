#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dll.h"
#include "binomial.h"

struct binomial
    {
    DLL *rootList;
    int size;
    void *extremeVal;
    void (*display)();
    int (*compare)();
    void (*update)();
    void (*free)();
    
    }

BINOMIAL *newBINOMIAL(void (*d)(void *,FILE *), int (*c)(void *,void *), void (*u)(void *,void *), void (*f)(void *))
    {
    
    BINOMIAL *b = malloc(sizeof(BINOMIAL));

    b->rootList = newDLL(d, f); //?? DIFF DISPLAY?
    b->size = 0;
    b->extremeVal = 0;
    b->display = d;
    b->compare = c;
    b->update = u;
    b->free = f;

    }

//This method inserts a generic value into the heap, returning the address of the private node that ends up 
//holding the inserted value. It should run in log time (worst case) and constant amortized time. 
void *insertBINOMIAL(BINOMIAL *b, void *value)
    {
    
    }

int sizeBINOMIAL(BINOMIAL *b)
    {
    return b->size;
    }

//This method destructively unions two BINOMIAL heaps. The first of the given heaps gets the contents of the second. 
//After the union, the second heap's rootlist should be empty. This method should run in log time. 
void unionBINOMIAL(BINOMIAL *r, BINOMIAL *d)
    {
    
    }

//This method removes the value contained in the passed-in node from the heap. It should run in log time. 
void deleteBINOMIAL(BINOMIAL *b,void *node)
    {

    }

//This method decreases the value contained in the second argument (the passed-in node) to the third argument.
// It should run in log time. 
void decreaseKeyBINOMIAL(BINOMIAL *b,void *node,void *value)
    {

    }

//This method non-destructively returns the extreme value in the heap. It should run in amortized constant time.
void *peekBINOMIAL(BINOMIAL *b)
    {
    
    }

//This method removes and returns the extreme value in the heap. Children of the node holding the extracted value are 
//added to an empty considation array. Then the root list is consolidated, from low degree to high degree. 
//The resulting rootlist should be ordered from low degree to high-degree. It should run in log time. 
void *extractBINOMIAL(BINOMIAL *b)
    {
    
    }

//This method should display the number of values in the heap and the size of the rootlist. If the heap is non-empty, 
//it should display the extreme value. Example: 
    // size: 14
    // rootlist size: 3
    // extreme: -40
void statisticsBINOMIAL(BINOMIAL *b,FILE *fp)
    {
    fprintf(fp, "size: %d\n", b->size);
    fprintf(fp, "rootlist size: %d\n", sizeDLL(b->rootList));
    if (b->size != 0) 
        {
        fprintf(fp, "extreme: ");
        b->display(b->extremeVal); //?? fix this??
        fprintf(fp, "\n");
        }
    }

//The method displays the rootlist values, from low degree to high degree, If a particular degree is missing, 
//the method should display NULL. The extreme value, if there is one, is printed with an asterisk. 
//A newline is printed after the last rootlist value. Example: 
//    rootlist: NULL 23 -40* 12
//In this example, there is no degree zero subheap, the degree one subheap is rooted by the value 23, and so on. 
void displayBINOMIAL(BINOMIAL *b,FILE *fp)
    {
    
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

    }

void freeBINOMIAL(BINOMIAL *b)
    {

    }
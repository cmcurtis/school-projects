#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"
#include "dll.h"

typedef struct NODE
    {
    void *value;
    struct NODE *next;
    struct NODE *prev;
    }NODE;

struct stack 
    {
    DLL *list;
    void (*display)();
    void (*free)();
    };

STACK *newSTACK(void (*d)(void *,FILE *),void (*f)(void *))
    {
    STACK *items = malloc(sizeof(STACK));
    assert(items != 0);
    items->list = newDLL(d, f);
    items->display = d;
    items->free = f;
    return items;
    }

//The push method runs in constant or amortized constant time. 
//The value to be pushed is stored in the underlying data structure. 
void push(STACK *items,void *value)
    {
    insertDLL(items->list, 0, value);
    return;
    }

//The pop method runs in constant or amortized constant time. 
//The value to be popped is removed in the underlying data structure. 
void *pop(STACK *items)
    {
    assert(sizeDLL(items->list) > 0);
    
    void* val = removeDLL(items->list, 0);
    return val;
    }

//The peek method returns the value ready to come off the stack, but leaves the stack unchanged. 
//It runs in constant time
void *peekSTACK(STACK *items)
    {
    assert(sizeDLL(items->list) > 0);
    
    void* val = getDLL(items->list, 0);
    return val;
    }

//The size method returns the number of items stored in the queue. It runs in amortized constant time.
int sizeSTACK(STACK *items)
    {
    return sizeDLL(items->list); 
    }

// The display method prints the items stored in the stack. If the integers 5, 6, 2, 9, and 1 are pushed in the order given, the method would generate this output:
//    |1,9,2,6,5|
//with no preceding or following whitespace. An empty stack displays as ||. 
void displaySTACK(STACK *items,FILE *fp)
    {
    fprintf(fp, "|");
    if (sizeDLL(items->list) != 0)
        {
        void *temp = 0;
        int index = 0;
        temp = getDLL(items->list, index);
        
        while (index != sizeDLL(items->list))
            {
            items->display(temp, fp);
            index++;
            if(index <= sizeDLL(items->list) - 1) { fprintf(fp, ","); }
            if(index != sizeDLL(items->list)){ temp = getDLL(items->list, index); }
            }
        }   
    fprintf(fp, "|");
    return;
    }

//This visualizing method simply calls the debug method of the underlying data structure. 
void displaySTACKdebug(STACK *items,FILE *fp)
    {
    displayDLLdebug(items->list, fp);
    return;
    }

//This method frees the stack by freeing the underlying data structure and then freeing the stack object itself.
void freeSTACK(STACK *items)
    {
    freeDLL(items->list);
    free(items); 
    }
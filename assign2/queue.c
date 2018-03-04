#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sll.h"
#include "queue.h"

typedef struct NODE
    {
    void *value;
    struct NODE *next;
    }NODE;

struct queue 
    {
    SLL *list;
    void (*display)();
    void (*free)();
    };

QUEUE *newQUEUE(void (*d)(void *,FILE *),void (*f)(void *))
    {
    QUEUE *items = malloc(sizeof(QUEUE));
    assert(items != 0);
    items->list = newSLL(d, f);
    items->display = d;
    items->free = f;
    return items;
    }

//The enqueue method runs in constant or amortized constant time. 
//The value to be enqueued is stored in the underlying data structure.
void enqueue(QUEUE *items,void *value)
    {
    insertSLL(items->list, sizeSLL(items->list), value);
    return;
    }


void *dequeue(QUEUE *items)
    {
    assert(sizeSLL(items->list) > 0);
    
    void* val = removeSLL(items->list, 0);
    return val;
    }

//The peek method returns the value ready to come off the queue, but leaves the queue unchanged. 
//It runs in constant time. 
void *peekQUEUE(QUEUE *items)
    {
    assert(sizeSLL(items->list) > 0);
    
    void* val = getSLL(items->list, 0);
    return val;
    }

//The size method returns the number of items stored in the queue. It runs in amortized constant time. 
int sizeQUEUE(QUEUE *items)
    {
    return sizeSLL(items->list); 
    }


void displayQUEUE(QUEUE *items,FILE *fp)
    {
    fprintf(fp, "<");
    //displaySLL(items->list, fp);
    if (sizeSLL(items->list) != 0)
        {
        void *temp = 0;
        int index = 0;
        temp = getSLL(items->list, index);
        
        while (index != sizeSLL(items->list))
            {
            items->display(temp, fp);
            index++;
            if(index <= sizeSLL(items->list) - 1) { fprintf(fp, ","); }
            if(index != sizeSLL(items->list)){ temp = getSLL(items->list, index); }
            }
        }   
    fprintf(fp, ">");
    return;
    }


void displayQUEUEdebug(QUEUE *items,FILE *fp)
    {
    displaySLLdebug(items->list, fp);
    return;
    }


void freeQUEUE(QUEUE *items)
    {
    freeSLL(items->list);
    free(items);   
    }

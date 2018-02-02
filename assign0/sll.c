#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sll.h"

typedef struct NODE
    {
    void *value;
    struct NODE *next;
    }NODE;
/*************** public interface *************/

/* constructors */
NODE *newNODE(void *v, NODE *n)
    {
    NODE *p = malloc(sizeof(NODE));
    if (p == 0) { fprintf(stderr,"out of memory\n"); exit(1); }
    p->value = v;
    p->next = n;
    return p;
    }

/* accessors */
void *getNODEvalue( NODE *n) { return n->value; }
NODE  *getNODEnext( NODE *n)  { return n->next; }

/* mutators */
void  setNODEvalue(NODE *n,void *v) { n->value = v; }
void  setNODEnext(NODE *n, NODE *p)  { n->next = p; }

void freeNODE(NODE *n,void (*release)(void *))
    {
    if (release != 0) release(n->value);
    free(n);
    }

    
struct sll
    {
        NODE *head;
        NODE *tail;
        int size;
        void (*display)();
        void (*free)();
    };

//d is the display function
//f is the freeing function
SLL *newSLL(void (*d)(void *,FILE *),void (*f)(void *))
    {
    SLL *items = malloc(sizeof(SLL));
    assert(items != 0);
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    items->free = f;
    return items;
    }

//inserts item at index specified
void insertSLL(SLL *items, int index, void *value)
    {
    assert(items != 0);
    assert(index <= items->size);
    assert(index >= 0);

    NODE *temp = NULL;
    NODE *inserted = NULL;
    inserted = newNODE(value, 0);
    temp = items->head;
    int count = 0;
    if (index == 0) 
        { 
        if (items->size == 0) 
            { 
                items->tail = inserted;
                items->head = inserted; 
                items->size++;
                return;
            }
        setNODEnext(inserted, items->head);
        items->head = inserted;
        }
    else if (index == items->size) 
        {
        if (items->size == 1) 
            {
            items->tail = inserted; 
            setNODEnext(items->head, items->tail); 
            items->size++;
            return;
            }
        setNODEnext(items->tail, inserted);
        items->tail = inserted;
        }
    else 
        {
        while(count != index - 1)
            {
            temp = getNODEnext(temp);
            count++;
            }
        setNODEnext(inserted, getNODEnext(temp));
        setNODEnext(temp, inserted); 
        }
    items->size++;
    }

//removes item at index specified
void *removeSLL(SLL *items, int index)
    {
    assert(items != 0);
    assert(index >= 0);
    assert(index < items->size);

    NODE *temp = 0;
    NODE *deleted = 0;
    void* val = 0;
    
    temp = items->head;
    int count = 0;
    if (index == 0) 
        {
        deleted = items->head;
        val = deleted->value;
        items->head = getNODEnext(items->head);
        }
    else 
        {
        while(count != index - 1)
            {
            temp = getNODEnext(temp);
            count++;
            }
        deleted = getNODEnext(temp);
        val = deleted->value;
        if (index == items->size - 1){ items->tail = temp; }
        setNODEnext(temp, getNODEnext(deleted));
        }
    items->size--;
    free(deleted);
    return val;
    }

//concatonates recipient list and donor list
void unionSLL(SLL *recipient, SLL *donor)
    {
    if (recipient->size == 0)
        {
        recipient->head = donor->head;
        recipient->tail = donor->tail;
        }
    else if (donor->size == 0)
        {
        return;
        }
    else
        {
        setNODEnext(recipient->tail, donor->head);
        recipient->tail = donor->tail;
        }
    recipient->size += donor->size;
    donor->head = donor->tail = 0;
    donor->size = 0;
    }

//returns the value at the given index
void *getSLL(SLL *items, int index)
    {
    assert(items != 0);
    assert(index < items->size);
    assert(index >= 0);

    NODE *temp = 0;
    temp = items->head;
    int count = 0;
    if (index == 0) { return getNODEvalue(items->head); }
    else if (index == items->size - 1) { return getNODEvalue(items->tail); }
    else
        {
        while(count != index)
            {
            temp = temp->next;
            count++;
            }
        return getNODEvalue(temp);
        }
    }

//method updates the value at the given index
//If the given index is a valid index for the list, the replaced value is returned. 
//If the given index is equal to the size, the value is appended to the list and a null pointer is returned
void *setSLL(SLL *items, int index, void *value)
    {
    assert(items != 0);
    assert(index <= items->size);
    assert(index >= 0);

    NODE *temp = 0;
    temp = items->head;
    void *val = 0;
    
    int count = 0;
    if (index == items->size) 
        {
        NODE *inserted = newNODE(value, NULL);
        if (items->size == 0) { items->head = items->tail = inserted; }
        else
            {
            setNODEnext(items->tail, inserted);
            items->tail = inserted;
            }
        items->size++;
        return 0;
        }
    else if (index == 0) 
        {
        val = getNODEvalue(items->head);
        setNODEvalue(items->head, value);
        return val;
        }
    else 
        {
        while(count != index)
            {
            temp = getNODEnext(temp);
            count++;
            }
        val = getNODEvalue(temp);
        setNODEvalue(temp, value);
        }
    return val;
    }

// returns number of items in the list
int sizeSLL(SLL *items)
    {
        return items->size;
    }


//prints the items stored in the list. 
//An empty list displays as {}. 
void displaySLL(SLL *items, FILE *fp)
    {
    fprintf(fp, "{");
    if (items->size != 0)
        {
        NODE *temp = 0;
        temp = items->head;
        while (temp != NULL)
            {
            items->display(temp->value, fp);
            if(temp->next != NULL) { fprintf(fp, ","); }
            temp = getNODEnext(temp);
            }
        }   
    fprintf(fp, "}");
    return;
    }

//
void displaySLLdebug(SLL *items, FILE *fp)
    {
    NODE *temp = 0;
    fprintf(fp, "head->{");
    if (items->size != 0) 
        {
        temp = items->head;
        while (temp != NULL)
            {
            items->display(temp->value, fp);
            if(temp->next != NULL) { fprintf(fp, ","); }
            temp = getNODEnext(temp);
            }
        }
    fprintf(fp, "},tail->{");
    if (items->size > 0)
        {
        items->display(items->tail->value, fp);
        }
    fprintf(fp, "}");
    return;
    }

//This method walks through the list, freeing the generic values (using the passed-in freeing function) 
//and the nodes that hold them. If the freeing function is null, the generic value is not freed.
void freeSLL(SLL *items)
    {
    NODE *temp = 0;
    NODE *deleted = 0;

    temp = items->head;
    while(temp != NULL)
        {
        deleted = temp;
        temp = getNODEnext(temp);
        freeNODE(deleted, items->free);
        }
    free(items);
    return;
    }
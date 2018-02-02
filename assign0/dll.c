#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"

typedef struct NODE
    {
    void *value;
    struct NODE *next;
    struct NODE *prev;
    }NODE;

/*************** public interface *************/

/* constructors */

NODE *
newNODE(void *v,NODE *n,NODE *prev)
    {
    NODE *p = malloc(sizeof(NODE));
    if (p == 0) { fprintf(stderr,"out of memory\n"); exit(1); }
    p->value = v;
    p->next = n;
    p->prev = prev;
    return p;
    }

/* accessors */

void  *getNODEvalue(NODE *n) { return n->value; }
NODE  *getNODEnext(NODE *n)  { return n->next; }
NODE  *getNODEprev(NODE *n)  { return n->prev; }

/* mutators */

void  setNODEvalue(NODE *n,void *v) { n->value = v; }
void  setNODEnext(NODE *n,NODE *p)  { n->next = p; }
void  setNODEprev(NODE *n,NODE *p)  { n->prev = p; }


void freeNODE(NODE *n,void (*release)(void *))
    {
    if (release != 0) release(n->value);
    free(n);
    }

//DLL definition
struct dll 
    {
    NODE *head;
    NODE *tail;
    int size;
    void (*display)();
    void (*free)();
    };


DLL *newDLL(void (*d)(void *,FILE *),void (*f)(void *))
    {
    DLL *items = malloc(sizeof(DLL));
    assert(items != 0);
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    items->free = f;
    return items;
    }

//It runs in constant time for insertions at a constant distance from the front and from the back. 
//The doubly-linked list uses zero-based indexing. 
void insertDLL(DLL *items,int index,void *value) // add case for index > items->size/2;
    {
    assert(items != 0);
    assert(index <= items->size);
    assert(index >= 0);

    NODE *inserted = NULL;
    inserted = newNODE(value, 0, 0);

    int count = 0;
    if (index == 0) 
        {
        if (items->size == 0) 
            { 
            items->tail = items->head = inserted;
            items->size++;
            return;
            }
        setNODEnext(inserted, items->head);
        setNODEprev(items->head, inserted);
        items->head = inserted;
        }
    else if (index == items->size) 
        {
        if (items->size == 1) 
            {
            items->tail = inserted; 
            setNODEnext(items->head, items->tail);
            setNODEprev(items->tail, items->head);
            items->size++;
            return;
            }
        setNODEprev(inserted, items->tail);
        setNODEnext(items->tail, inserted);
        items->tail = inserted;
        }
    else 
        {
        NODE *temp = NULL;
        if (index > (items->size / 2) && items->size > 3)
            {
            temp = items->tail;
            count = items->size;
            while (count != index)
                {
                temp = getNODEprev(temp);
                count--;
                }
            setNODEnext(inserted, temp->next);
            setNODEprev(inserted, temp);
            setNODEprev(temp->next, inserted);
            setNODEnext(temp, inserted);
            }
        else
            {
            temp = items->head;
            while(count != index - 1)
                {
                temp = getNODEnext(temp);
                count++;
                }
            setNODEnext(inserted, temp->next);
            setNODEprev(inserted, temp);
            setNODEprev(temp->next, inserted);
            setNODEnext(temp, inserted);
            }
        
        }
    
    items->size++;
    
    }

//It runs in constant time for removals at a constant distance from the front and from the back. 
void *removeDLL(DLL *items,int index) // add case for index > items->size/2;
    {
    assert(items != 0);
    assert(index >= 0);
    assert(index < items->size);

    NODE *temp = 0;
    NODE *deleted = 0;
    void *val = 0;

    temp = items->head;
    int count = 0;
    if (index == 0) 
        {
        deleted = temp;
        items->head = getNODEnext(temp);
        items->size--;
        val = getNODEvalue(deleted);
        free(deleted);
        return val;
        }
    else if (index == items->size - 1)
        {
        deleted = items->tail;
        if(items->size == 2) 
            {
            items->tail = items->head;
            setNODEnext(items->tail, 0);
            items->size--;
            val = getNODEvalue(deleted);
            free(deleted);
            return val;
            }
        val = getNODEvalue(deleted);
        items->tail = deleted->prev;
        setNODEnext(items->tail, 0);
        free(deleted);
        }
    else 
        {
        if (index > (items->size / 2) && items->size > 3)
            {
            temp = items->tail;
            count = items->size - 1;
            while (count != index)
                {
                temp = getNODEprev(temp);
                count--;
                }
            deleted = temp;
            val = getNODEvalue(deleted);
            free(deleted);
            setNODEnext(getNODEprev(temp), getNODEnext(temp));
            if (index == items->size - 2) 
                {
                    setNODEprev(items->tail, getNODEprev(temp));
                    setNODEnext(getNODEprev(temp), items->tail);
                }
            else 
                { 
                setNODEprev(getNODEnext(temp), getNODEprev(temp));
                setNODEnext(getNODEprev(temp), getNODEnext(temp));
                }
            }
        else
            {
            while(count <= index - 1)
                {
                temp = getNODEnext(temp);
                count++;
                }
            deleted = temp;
            val = getNODEvalue(deleted);
            setNODEnext(getNODEprev(temp), getNODEnext(temp));
            setNODEprev(getNODEnext(temp), getNODEprev(temp));
            free(deleted);
            }
        }
    items->size--;
    
    return val;
    }

//concatonates recipient list and donor list
void unionDLL(DLL *recipient,DLL *donor)
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
        setNODEprev(donor->head, recipient->tail);
        recipient->tail = donor->tail;
        }
    recipient->size += donor->size;
    donor->head = donor->tail = 0;
    donor->size = 0;
    }

//The method returns the value at the given index. 
//It runs in constant time for retrievals at a constant distance from the front and from the back. 
void *getDLL(DLL *items,int index)
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

//The method updates the value at the given index. 
//If the given index is a valid index for the list, the replaced value is returned. 
//If the given index is equal to the size, the value is appended to the list and a null pointer is returned. 
//It runs in constant time for updates at a constant distance from the front and from the back. 
void *setDLL(DLL *items,int index,void *value)
    {
    assert(items != 0);
    assert(index <= items->size);
    assert(index >= 0);
        
    NODE *temp = 0;
    temp = items->head;
    void *val = 0;

    int count = 0;
    if (index == 0) 
        {
        val = getNODEvalue(items->head);
        setNODEvalue(items->head, value);
        return val;
        }
    else if (index == items->size) 
        {
        NODE *inserted = newNODE(value, NULL, items->tail);
        setNODEnext(items->tail, inserted);
        items->tail = inserted;
        items->size++;
        return 0;
        }
    else 
        {
        if (index > (items->size / 2) && items->size > 3)
            {
            temp = items->tail;
            count = items->size - 1;
            while (count != index)
                {
                temp = getNODEprev(temp);
                count--;
                }
            }
        else
            {
            while(count != index)
                {
                temp = getNODEnext(temp);
                count++;
                }
            }
        val = getNODEvalue(temp);
        setNODEvalue(temp, value);
        }
    return val;
    }

//returns size of the doubly linked list
int sizeDLL(DLL *items)
    {
        return items->size;
    }

//The display method prints the items stored in the list. If the list holds the integers 5, 6, 2, 9, and 1, with 5 at the front and 1 at the back, the method would generate this output:
//{{5,6,2,9,1}}
//with no preceding or following whitespace. An empty list displays as {{}}. 
void displayDLL(DLL *items,FILE *fp)
    {
    fprintf(fp, "{{");
    if (items->size != 0)
        {
        NODE *temp = 0;
        temp = items->head;
        while (temp != 0)
            {
            items->display(temp->value, fp);
            if(temp->next != 0) { fprintf(fp, ","); }
            temp = getNODEnext(temp);
            }
        }   
    fprintf(fp, "}}");
    
    return;
    }

void displayDLLdebug(DLL *items,FILE *fp)
    {
    NODE *temp = 0;
    fprintf(fp, "head->{{");
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
    fprintf(fp, "}},tail->{{");
    if (items->size > 0)
        {
        items->display(items->tail->value, fp);
        }
    fprintf(fp, "}}");
    return;
    }

//this method walks through the list, freeing the generic values (using the passed-in freeing function) 
//and the nodes that hold them. 
//If the freeing function is null, the generic value is not freed.
void freeDLL(DLL *items)
    {
    NODE *temp = 0;
    NODE *deleted = 0;

    temp = items->head;
    while(temp != 0)
        {
        deleted = temp;
        temp = getNODEnext(temp);
        freeNODE(deleted, items->free);
        }
    free(items);
    return;
    }


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"

typedef struct DLLNODE
    {
    void *value;
    struct DLLNODE *next;
    struct DLLNODE *prev;
    }DLLNODE;

/*************** public interface *************/

/* constructors */

DLLNODE *
newDLLNODE(void *v, DLLNODE *n, DLLNODE *prev)
    {
    DLLNODE *p = malloc(sizeof(DLLNODE));
    if (p == 0) { fprintf(stderr,"out of memory\n"); exit(1); }
    p->value = v;
    p->next = n;
    p->prev = prev;
    return p;
    }

/* accessors */

void  *getDLLNODEvalue(DLLNODE *n) { return n->value; }
DLLNODE  *getDLLNODEnext(DLLNODE *n)  { return n->next; }
DLLNODE  *getDLLNODEprev(DLLNODE *n)  { return n->prev; }

/* mutators */

void  setDLLNODEvalue(DLLNODE *n,void *v) { n->value = v; }
void  setDLLNODEnext(DLLNODE *n,DLLNODE *p)  { n->next = p; }
void  setDLLNODEprev(DLLNODE *n,DLLNODE *p)  { n->prev = p; }


void freeDLLNODE(DLLNODE *n,void (*release)(void *))
    {
    if (release != 0) release(n->value);
    free(n);
    }

struct dll 
    {
    DLLNODE *head;
    DLLNODE *tail;
    DLLNODE *curr;
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
    items->curr = 0;
    items->size = 0;
    items->display = d;
    items->free = f;
    return items;
    }


void* insertDLL(DLL *items,int index,void *value)
    {
    assert(items != 0);
    assert(index <= items->size);
    assert(index >= 0);

    DLLNODE *inserted = NULL;
    inserted = newDLLNODE(value, 0, 0);

    int count = 0;
    if (index == 0) 
        {
        if (items->size == 0) 
            { 
            items->tail = items->head = inserted;
            items->size++;
            return inserted;
            }
        setDLLNODEnext(inserted, items->head);
        setDLLNODEprev(items->head, inserted);
        items->head = inserted;
        }
    else if (index == items->size) 
        {
        if (items->size == 1) 
            {
            items->tail = inserted; 
            setDLLNODEnext(items->head, items->tail);
            setDLLNODEprev(items->tail, items->head);
            items->size++;
            return inserted;
            }
        setDLLNODEprev(inserted, items->tail);
        setDLLNODEnext(items->tail, inserted);
        items->tail = inserted;
        }
    else 
        {
        DLLNODE *temp = NULL;
        if (index > (items->size / 2) && items->size > 3)
            {
            temp = items->tail;
            count = items->size;
            while (count != index)
                {
                temp = getDLLNODEprev(temp);
                count--;
                }
            setDLLNODEnext(inserted, temp->next);
            setDLLNODEprev(inserted, temp);
            setDLLNODEprev(temp->next, inserted);
            setDLLNODEnext(temp, inserted);
            }
        else
            {
            temp = items->head;
            while(count != index - 1)
                {
                temp = getDLLNODEnext(temp);
                count++;
                }
            setDLLNODEnext(inserted, temp->next);
            setDLLNODEprev(inserted, temp);
            setDLLNODEprev(temp->next, inserted);
            setDLLNODEnext(temp, inserted);
            }
        
        }
    
    items->size++;
    
    return inserted;
    }

void *removeDLL(DLL *items,int index)
    {
    assert(items != 0);
    assert(index >= 0);
    assert(index < items->size);

    DLLNODE *temp = 0;
    DLLNODE *deleted = 0;
    void *val = 0;

    temp = items->head;
    int count = 0;
    if (index == 0) 
        {
        deleted = temp;
        items->head = getDLLNODEnext(temp);
        items->size--;
        val = getDLLNODEvalue(deleted);
        free(deleted);
        //if(items->curr == temp) { items->curr = items->head; }
        return val;
        }
    else if (index == items->size - 1)
        {
        deleted = items->tail;
        if(items->size == 2) 
            {
            items->tail = items->head;
            setDLLNODEnext(items->tail, 0);
            items->size--;
            val = getDLLNODEvalue(deleted);
            //if(items->curr == temp) { items->curr = items->head; }
            free(deleted);
            return val;
            }
        val = getDLLNODEvalue(deleted);
        items->tail = deleted->prev;
        //if(items->curr == temp) { items->curr = items->tail; }
        setDLLNODEnext(items->tail, 0);
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
                temp = getDLLNODEprev(temp);
                count--;
                }
            deleted = temp;
            val = getDLLNODEvalue(deleted);
            setDLLNODEnext(getDLLNODEprev(temp), getDLLNODEnext(temp));
            if (index == items->size - 2) 
                {
                    setDLLNODEprev(items->tail, getDLLNODEprev(temp));
                    setDLLNODEnext(getDLLNODEprev(temp), items->tail);
                }
            else 
                { 
                setDLLNODEprev(getDLLNODEnext(temp), getDLLNODEprev(temp));
                setDLLNODEnext(getDLLNODEprev(temp), getDLLNODEnext(temp));
                }
            //if(items->curr == temp) { nextDLL(items); }
            free(deleted);
            }
        else
            {
            while(count <= index - 1)
                {
                temp = getDLLNODEnext(temp);
                count++;
                }
            deleted = temp;
            val = getDLLNODEvalue(deleted);
            //if(items->curr == temp) { nextDLL(items); }
            setDLLNODEnext(getDLLNODEprev(temp), getDLLNODEnext(temp));
            setDLLNODEprev(getDLLNODEnext(temp), getDLLNODEprev(temp));
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
        setDLLNODEnext(recipient->tail, donor->head);
        setDLLNODEprev(donor->head, recipient->tail);
        recipient->tail = donor->tail;
        }
    recipient->size += donor->size;
    donor->head = donor->tail = 0;
    donor->size = 0;
    }

void *getDLL(DLL *items,int index)
    {
    assert(items != 0);
    assert(index < items->size);
    assert(index >= 0);

    DLLNODE *temp = 0;
    temp = items->head;
    int count = 0;
    if (index == 0) { return getDLLNODEvalue(items->head); }
    else if (index == items->size - 1) { return getDLLNODEvalue(items->tail); }
    else
        {
        if (index > (items->size / 2) && items->size > 3)
            {
            temp = items->tail;
            count = items->size - 1;
            while (count != index)
                {
                temp = getDLLNODEprev(temp);
                count--;
                }
            }
        else
            {
                while(count != index)
                {
                temp = getDLLNODEnext(temp);
                count++;
                }
            }
        return getDLLNODEvalue(temp);
        }
    }


void *setDLL(DLL *items,int index,void *value)
    {
    assert(items != 0);
    assert(index <= items->size);
    assert(index >= 0);
        
    DLLNODE *temp = 0;
    temp = items->head;
    void *val = 0;

    int count = 0;
    if (index == 0) 
        {
        val = getDLLNODEvalue(items->head);
        setDLLNODEvalue(items->head, value);
        return val;
        }
    else if (index == items->size) 
        {
        DLLNODE *inserted = newDLLNODE(value, NULL, items->tail);
        setDLLNODEnext(items->tail, inserted);
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
                temp = getDLLNODEprev(temp);
                count--;
                }
            }
        else
            {
            while(count != index)
                {
                temp = getDLLNODEnext(temp);
                count++;
                }
            }
        val = getDLLNODEvalue(temp);
        setDLLNODEvalue(temp, value);
        }
    return val;
    }

int sizeDLL(DLL *items)
    {
    return items->size;
    }

void displayDLL(DLL *items,FILE *fp)
    {
    fprintf(fp, "{{");
    if (items->size != 0)
        {
        DLLNODE *temp = 0;
        temp = items->head;
        while (temp != 0)
            {
            items->display(temp->value, fp);
            if(temp->next != 0) { fprintf(fp, ","); }
            temp = getDLLNODEnext(temp);
            }
        }   
    fprintf(fp, "}}");
    
    return;
    }

void displayDLLdebug(DLL *items,FILE *fp)
    {
    DLLNODE *temp = 0;
    fprintf(fp, "head->{{");
    if (items->size != 0) 
        {
        temp = items->head;
        while (temp != NULL)
            {
            items->display(temp->value, fp);
            if(temp->next != NULL) { fprintf(fp, ","); }
            temp = getDLLNODEnext(temp);
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

void freeDLL(DLL *items)
    {
    DLLNODE *temp = 0;
    DLLNODE *deleted = 0;

    temp = items->head;
    while(temp != 0)
        {
        deleted = temp;
        temp = getDLLNODEnext(temp);
        freeDLLNODE(deleted, items->free);
        }
    free(items);
    return;
    }

//sets the head and tail to null, the size to zero. Only freeing of list DLLNODEs, not values, is to be done. 
void removeDLLall(DLL *items)
    {
    // printf("IN REMOVE DLL ALL \n");
    // if (items == NULL) return;
    // DLLNODE *temp = 0;
    // DLLNODE *deleted = 0;
    // displayDLL(items, stdout);
    // printf("\n");
    // firstDLL(items);
    // while(moreDLL(items))
    //     {
    //     temp = currentDLL(items);
    //     printf("removing node: ");
    //     items->display(temp, stdout);
    //     printf("\n");
    //     deleted = temp;
    //     nextDLL(items);
    //     free(deleted);
    //     }
    
    items->head = 0;
    items->tail = 0;
    items->curr = 0;
    items->size = 0;
    }

//removes the given DLLNODE from the linked list, return the value of the removed DLLNODE 
void *removeDLLnode(DLL *items, void *n)
    {
    DLLNODE *temp = n;
    void *val = getDLLNODEvalue(temp);
    // printf("IN REMOVE DLL NODE \n");
    DLLNODE *next = temp->next;
    DLLNODE *prev = temp->prev;
    if (temp == items->head) 
        {
        if (items->size == 1) 
            {
            items->head = NULL;
            items->curr = NULL;
            items->size--;
            free(temp);
            return val;
            }
        else items->head = next;
        }
    if (temp == items->tail)
        {
        if (items->size == 1) 
            {
            items->tail = NULL;
            items->curr = NULL;
            items->size--;
            free(temp);
            return val;
            }
        else items->tail = prev;
        }

    if (next != 0) setDLLNODEprev(next, prev);
    if (prev != 0) setDLLNODEnext(prev, next);

    if (temp == items->curr)
        {
        if (next != 0) nextDLL(items);
        else prevDLL(items);
        }

    free(temp);
    items->size--;
    return val;
    }
 
void firstDLL(DLL *items)
    {
    //printf("FIRST DLL\n");
    items->curr = items->head;
    }

void lastDLL(DLL *items)
    {
    //printf("LAST DLL\n");
    items->curr = items->tail;
    }

int moreDLL(DLL *items)
    {
    //printf("MORE DLL\n");
    if (items->curr != NULL) return 1;
    else return 0;
    }

void nextDLL(DLL *items)
    {
    //printf("NEXT DLL\n");
    assert(items->curr != 0);
    items->curr = getDLLNODEnext(items->curr);
    }

void prevDLL(DLL *items)
    {
    //printf("PREV DLL\n");
    assert(items->curr != 0);
    items->curr = getDLLNODEprev(items->curr);
    }

void *currentDLL(DLL *items)
    {
    //printf("CURRENT DLL\n");
    assert(items->curr != 0);
    return getDLLNODEvalue(items->curr);
    }
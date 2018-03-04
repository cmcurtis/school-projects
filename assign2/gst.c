#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "gst.h"
#include "bst.h"


typedef struct gstvalue{ 
    void *value;
    int count;
    void (*display)();
    int (*compare)();
    void (*free)();
}GSTVALUE;

GSTVALUE *newGSTVALUE(void *value, void (*d)(void *, FILE *), int (*c)(void *,void *), void (*f)(void *))
    {
    GSTVALUE *v = malloc(sizeof(GSTVALUE));
    assert(v != 0);

    v->value = value;
    v->count = 1;
    v->display = d;
    v->compare = c;
    v->free = f;

    return v;
    }

//accessors
int getGSTVALUEcount(GSTVALUE *v) { return v->count; }
void* getGSTVALUEvalue(GSTVALUE *v) {return v->value; }

//mutators
void setGSTVALUEvalue(GSTVALUE *v, void *value) { v->value = value; }
void setGSTVALUEcount(GSTVALUE *v, int newCount) { v->count = newCount; }

int gcompare(void *n, void *m)
    {
    GSTVALUE *v = n;
    GSTVALUE *w = m;

    void *valV = getGSTVALUEvalue(v);
    void *valW = getGSTVALUEvalue(w);

    return v->compare(valV, valW);
    }

void gdisplay(void *v, FILE *fp)
    {
    GSTVALUE* w = v;
    w->display(getGSTVALUEvalue(w), fp);
    if (getGSTVALUEcount(w) != 1) { fprintf(fp, "[%d]", getGSTVALUEcount(w)); }
    }

void gfree(void *v) // TODO: FIX
    {
    GSTVALUE *w = v;
    void *val = getGSTVALUEvalue(w);
    if (w->free != NULL) { w->free(val); }
    free(w);
    }

struct gst {
    BST *tree;
    int size;
    void (*display)();
    int (*compare)();
    void (*free)();
};

GST *newGST(void (*d)(void *, FILE *), int (*c)(void *,void *), void (*f)(void *)) 
    {
    GST *g = malloc(sizeof(GST));
    assert(g != 0);

    g->tree = newBST(gdisplay, gcompare, 0, gfree);
    g->size = 0;
    g->display = d;
    g->compare = c;
    g->free = f;

    return g;
    }


void insertGST(GST *g, void *value)
    {
    if (sizeGST(g) == 0) //first node in empty-tree; 
        { 
            GSTVALUE *new = newGSTVALUE(value, g->display, g->compare, g->free);
            insertBST(g->tree, new); 
            g->size += 1;
        }
    else 
        {
        GSTVALUE *temp = findGST(g, value);
        if (temp == NULL) //node value does not exist in tree;
            {
            GSTVALUE *new = newGSTVALUE(value, g->display, g->compare, g->free);
            insertBST(g->tree, new); 
            g->size += 1;
            }
        else  // node value exists in tree
            {
            setGSTVALUEcount(temp, getGSTVALUEcount(temp) + 1);
            g->size += 1;
            }
        }
    }


//finds count of a GSTVALUE in the bst
int findGSTcount(GST *g, void *value)
    {
    GSTVALUE *temp = findGST(g, value);
    int count = getGSTVALUEcount(temp);
    return count;
    }


//finds the GSTVALUE in the bst, returns null if not in tree
void *findGST(GST *g, void *value)
    {
    assert (g != 0);
    
    GSTVALUE *find = newGSTVALUE(value, g->display, g->compare, g->free);
    BSTNODE *temp = findBST(g->tree, find);

    if (temp == 0) { return 0; }
    
    GSTVALUE *found = getBSTNODEvalue(temp);
    free(find);
    return found;
    }


void *deleteGST(GST *g,void *value)
    {
    assert(g != 0);
    GSTVALUE *temp = findGST(g, value);

    if (temp == 0) { return 0; } //value not in tree
    
    else if (getGSTVALUEcount(temp) > 1) //node has duplicates
        {
        setGSTVALUEcount(temp, getGSTVALUEcount(temp) - 1);
        g->size -= 1;
        return temp;
        }
    else //node has no duplicates
        {
        BSTNODE *deleted = deleteBST(g->tree, temp);
        g->size -= 1;
        return getBSTNODEvalue(deleted);
        }
    }

int sizeGST(GST *g)
    {
    return g->size;
    }

int duplicates(GST *g)
    {
    return sizeGST(g) - sizeBST(g->tree);
    }

void statisticsGST(GST *g, FILE *fp)
    {
    fprintf(fp, "Duplicates: %d\n", duplicates(g));

    statisticsBST(g->tree, fp);
    }

////The method calls the tree using a level-order traversal via decorated display of the underlying structure
void displayGST(GST *g, FILE *fp) 
    {
    displayBSTdecorated(g->tree, fp);
    }

//The method calls the display method of the underlying data structure.
void displayGSTdebug(GST *g, FILE *fp)
    {
    displayBST(g->tree, fp);
    }

void freeGST(GST *g)
    {
    freeBST(g->tree);
    free(g);
    }

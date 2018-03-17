#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "avl.h"
#include "bst.h"


static void deletionFixup(BSTNODE *n);
static void updateBalance(BSTNODE *n);
static void insertionFixup(BSTNODE *n);
static BSTNODE* sibling(BSTNODE *n);
static BSTNODE* favorite(BSTNODE *n);
static int linear(BSTNODE *c, BSTNODE *p, BSTNODE *gp);


typedef struct avlvalue {
    void *value;
    int count;
    int balance;
    int height;
    int rHeight;
    int lHeight;
    void (*display)();
    int (*compare)();
    void (*free)();
}AVLVALUE;

AVLVALUE *newAVLVALUE(void *value, void (*d)(void *,FILE *), int (*c)(void *,void *), void (*f)(void *))
    {
    AVLVALUE *n = malloc(sizeof(AVLVALUE));
    assert (n != 0);

    n->value = value;
    n->count = 1;
    n->height = 0;
    n->rHeight = 0;
    n->lHeight = 0;
    n->balance = 0;
    n->display = d;
    n->compare = c;
    n->free = f;

    return n;
    }

static AVLVALUE* findAVLVALUE(AVL *a, void *value);

//accessors
int getAVLVALUEcount(AVLVALUE *v) { return v->count; }
void* getAVLVALUEvalue(AVLVALUE *v) { return v->value; }
int getAVLVALUEbalance(AVLVALUE *v) { return v->balance; }
int getAVLVALUEheight(AVLVALUE *v) { return v->height; }
int getAVLVALUElHeight(AVLVALUE *v) { return v->lHeight; }
int getAVLVALUErHeight(AVLVALUE *v) { return v->rHeight; }

//mutators
void setAVLVALUEvalue(AVLVALUE *v, void *value) { v->value = value; }
void setAVLVALUEcount(AVLVALUE *v, int newCount) { v->count = newCount; }
void setAVLVALUEheight(AVLVALUE *v, int h) { v->height = h; }
void setAVLVALUElHeight(AVLVALUE *v, int l) { v->lHeight = l; }
void setAVLVALUErHeight(AVLVALUE *v, int r) { v->rHeight = r; }
void setAVLVALUEbalance(AVLVALUE *v) { v->balance = v->lHeight - v->rHeight; }

int acompare(void *n, void *m)
    {
    AVLVALUE *v = n;
    AVLVALUE *w = m;

    void *valV = getAVLVALUEvalue(v);
    void *valW = getAVLVALUEvalue(w);

    return v->compare(valV, valW);
    }

void aswap(BSTNODE *a, BSTNODE *b)
    {
    AVLVALUE *ta = getBSTNODEvalue(a);
    AVLVALUE *tb = getBSTNODEvalue(b);

    /* swap the values stored in the AVL value objects */
    void *vtemp = ta->value;
    ta->value = tb->value;
    tb->value = vtemp;

    /* swap the counts stored in the AVL value objects */
    int ctemp = ta->count;
    ta->count = tb->count;
    tb->count = ctemp;

    /* note: AVL heights and balance factors are NOT swapped */
    }

void adisplay(void *n, FILE *fp)
    {
    AVLVALUE* w = getBSTNODEvalue(n);
    w->display(getAVLVALUEvalue(w), fp);
    if (getAVLVALUEcount(w) != 0) { fprintf(fp, "[%d]", getAVLVALUEcount(w)); }
    if (getAVLVALUEbalance(w) == 1) { fprintf(fp, "+"); }
    if (getAVLVALUEbalance(w) == -1) { fprintf(fp, "-"); }
    }

void afree(void *v)
    {
    AVLVALUE *w = v;
    if (w->free != NULL) w->free(getAVLVALUEvalue(w));
    free(w);
    }

struct avl{
    BST *tree;
    int size;
    int duplicates;
    void (*display)();
    int (*compare)();
    void (*free)();
};

AVL *newAVL( void (*d)(void *,FILE *), int (*c)(void *,void *), void (*f)(void *))
    {
    AVL *a = malloc(sizeof(AVL));
    assert(a != 0);

    a->tree = newBST(adisplay, acompare, aswap, afree);
    a->size = 0;
    a->duplicates = 0;
    a->display = d;
    a->compare = c;
    a->free = f;

    return a;
    }


void insertAVL(AVL *a, void *value)
    {
    if (sizeAVL(a) == 0) //first node in empty-tree; 
        { 
            AVLVALUE *new = newAVLVALUE(value, a->display, a->compare, a->free);
            insertBST(a->tree, new); 
            a->size += 1;
        }
    else 
        {
        AVLVALUE *temp = findAVLVALUE(a, value);
        if (temp == 0) //node value does not exist in tree;
            {
            AVLVALUE *new = newAVLVALUE(value, a->display, a->compare, a->free);
            BSTNODE *inserted = insertBST(a->tree, new); 
            a->size += 1;
            insertionFixup(inserted);
            }
        else  // node value exists in tree
            {
            setAVLVALUEcount(temp, getAVLVALUEcount(temp) + 1);
            a->size += 1;
            }
        }
    }


//This method returns the frequency of the searched-for value. If the value is not in the tree, the method should return zero. 
int findAVLcount(AVL *a, void *value)
    {
    AVLVALUE *temp = findAVLVALUE(a, value);
    return getAVLVALUEcount(temp);
    }


//This method returns the searched-for value. If the value is not in the tree, the method should return NULL. 
void *findAVL(AVL *a, void *value)
    {
    assert(a != 0);

    AVLVALUE *find = findAVLVALUE(a, value);

    if (find == 0) { return 0; }
    
    void *found = getAVLVALUEvalue(find);
    return found;
    }


void *deleteAVL(AVL *a, void *value)
    {
    assert(a != 0);
    AVLVALUE *temp = findAVLVALUE(a, value);

    if (temp == 0) //value not in tree
        {
        printf("Value ");
        a->display(value, stdout);
        printf(" not found.");
        return 0;
        }
    
    else if (getAVLVALUEcount(temp) > 1) //node has duplicates
        {
        setAVLVALUEcount(temp, getAVLVALUEcount(temp) - 1);
        a->size -= 1;
        return getAVLVALUEvalue(temp);
        }
    else //node has no duplicates ??TODO: create delete helper function
        {
        BSTNODE *deleted = findBST(a->tree, temp);
        swapToLeafBST(a->tree, deleted);
        deletionFixup(deleted);
        pruneLeafBST(a->tree, deleted);
        return getAVLVALUEvalue(temp);
        }
    }


int sizeAVL(AVL *a)
    {
    return a->size;
    }


int duplicatesAVL(AVL *a)
    {
    return sizeAVL(a) - sizeBST(a->tree);
    }


void statisticsAVL(AVL *a, FILE *fp)
    {
    fprintf(fp, "Duplicates: %d\n", duplicatesAVL(a));
    
    statisticsBST(a->tree, fp);
    }

//The method calls the tree using a level-order traversal via decorated display of the underlying structure
void displayAVL(AVL *a, FILE *fp)
    {
    displayBSTdecorated(a->tree, fp);
    }

//The method calls the display method of the underlying data structure.
void displayAVLdebug(AVL *a, FILE *fp)
    {
    displayBST(a->tree, fp);
    }


void freeAVL(AVL *a)
    {
    freeBST(a->tree);
    free(a);
    }



//helper functions
AVLVALUE* findAVLVALUE(AVL *a, void *value)
    {
    assert(a != 0);

    AVLVALUE *find = newAVLVALUE(value, a->display, a->compare, a->free);
    BSTNODE *temp = findBST(a->tree, find);

    if (temp == 0) { return 0; }
    
    AVLVALUE *found = getBSTNODEvalue(temp);
    free(find);
    return found;
    }


void insertionFixup(BSTNODE *n)
    {
    while(1)
        {
        BSTNODE *par = getBSTNODEparent(n);
        if (par == 0) { break; }

        BSTNODE *sib = sibling(n);
        AVLVALUE *x = getBSTNODEvalue(n);
        AVLVALUE *p = getBSTNODEvalue(par);

        if (sib != 0) 
            {
            AVLVALUE *sibVal = getBSTNODEvalue(sib);
            if (getAVLVALUEheight(sibVal) > getAVLVALUEheight(x)) //parent favors the sibling
                {
                updateBalance(par);
                break;
                }
            }
        else if (getAVLVALUEbalance(p) == 0) //parent is balanced
            {
            updateBalance(par);
            n = par; //update parent pointers
            continue;
            }
        else
            {// p is parent, y is fav of x
            BSTNODE *favChild = favorite(n);
            if (favChild != 0 && linear(favChild, n, par) == 0) //y exists and y,x,p are not linear
                {
                aswap(favChild, n); //rotate y to x
                aswap(favChild, par); //rotate y to p ???
                updateBalance(n);
                updateBalance(par);
                updateBalance(favChild);
                }
            else                                   //case 4
                {
                aswap(n, par); //rotate x to p
                updateBalance(par); //set the balance of p
                updateBalance(n); //set the balance of x
                }
            break;
            }
        }
    }

void deletionFixup(BSTNODE *n) //TODO FIX UP
    {
    AVLVALUE *x = getBSTNODEvalue(n);
    int xheight = getAVLVALUEheight(x);
    setAVLVALUEheight(x, 0);
    while(1)
        {
            
        BSTNODE *par = getBSTNODEparent(n);
        if (par == NULL) { break; }

        BSTNODE *sib = sibling(n);
        AVLVALUE *z = getBSTNODEvalue(sib);
        AVLVALUE *p = getBSTNODEvalue(par);
        AVLVALUE *x = getBSTNODEvalue(n);

        if (xheight > getAVLVALUEheight(z))  //parent favors n
            {
            setAVLVALUEheight(x, 0);
            updateBalance(par);
            n = par;
            continue;
            }
        setAVLVALUEheight(x, 0);
        if (getAVLVALUEbalance(p) == 0)  //parent has no favorite
            {
            updateBalance(par);
            break;
            }
        else 
            { // p is parent, z is sibiling, y is fav of z
            BSTNODE *favChild = favorite(sib);
            if (favChild != 0 && linear(favChild, sib, par) == 0) //y exists and y,z,p are not linear
                {
                aswap(favChild, sib);// rotate y to z
                aswap(favChild, par);// rotate y to p???
                updateBalance(par); // set the balance of p
                updateBalance(sib); // set the balance of z
                updateBalance(favChild); // set the balance of y
                n = favChild; //??? OR SIB???
                continue;
                }
            else
                {
                aswap(favChild, par); //rotate z to p
                updateBalance(par); // set the balance of p
                updateBalance(sib); // set the balance of z
                if (favChild == 0) break;
                n = sib; //??? or p???
                continue;
                }
            }
        }
    }

void updateBalance(BSTNODE *n)
    {
    BSTNODE *l = getBSTNODEleft(n);
    BSTNODE *r = getBSTNODEright(n);
    
    AVLVALUE *a = getBSTNODEvalue(n);

    //set n's left height
    if (l == 0) { setAVLVALUElHeight(a, 0); }
    else
        {
        AVLVALUE *left = getBSTNODEvalue(l);
        setAVLVALUElHeight(a, getAVLVALUEheight(left));
        }
    
    //set n's right height
    if (r == 0) { setAVLVALUErHeight(a, 0); }
    else 
        {
        AVLVALUE *right = getBSTNODEvalue(r);
        setAVLVALUErHeight(a, getAVLVALUEheight(right));
        }
    
    //set n's height to max +1
    if (getAVLVALUElHeight(a) > getAVLVALUErHeight(a)) { setAVLVALUEheight(a, getAVLVALUElHeight(a) + 1); }
    else setAVLVALUEheight(a, getAVLVALUErHeight(a) + 1);

    setAVLVALUEbalance(a);
    }

BSTNODE* sibling(BSTNODE *n)
    {
    BSTNODE *temp = getBSTNODEparent(n);
    if (temp == 0) { return 0; }
    
    if (getBSTNODEleft(temp) == n) { return getBSTNODEright(temp); }
    if (getBSTNODEright(temp) == n) { return getBSTNODEleft(temp); }
    return 0;
    }

BSTNODE* favorite(BSTNODE *n)
    {
    AVLVALUE *a = getBSTNODEvalue(n);

    if (getAVLVALUElHeight(a) > getAVLVALUErHeight(a)) { return getBSTNODEleft(n); }
    if (getAVLVALUErHeight(a) > getAVLVALUElHeight(a)) { return getBSTNODEright(n); }
    return 0;
    }


int linear(BSTNODE *c, BSTNODE *p, BSTNODE *gp)
    {
    return (getBSTNODEleft(gp) == p && getBSTNODEleft(p) == c)
        || (getBSTNODEright(gp) == p && getBSTNODEright(p) == c);
    }
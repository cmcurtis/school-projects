#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "avl.h"
#include "bst.h"


static void deletionFixup(BST *t, BSTNODE *n);
static void updateBalance(BSTNODE *n);
static void insertionFixup(BST *t, BSTNODE *n);
static BSTNODE* sibling(BSTNODE *n);
static BSTNODE* favorite(BSTNODE *n);
static int linear(BSTNODE *c, BSTNODE *p, BSTNODE *gp);
static void rightRotate(BST *t, BSTNODE *n);
static void leftRotate(BST *t, BSTNODE *n);
static void freeAVLVALUE(void *a);


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
    AVLVALUE* w = n;
    w->display(getAVLVALUEvalue(w), fp);
    if (getAVLVALUEcount(w) != 1) { fprintf(fp, "[%d]", getAVLVALUEcount(w)); }
    //printf("*%d*", getAVLVALUEbalance(w));
    if (getAVLVALUEbalance(w) == 1) { fprintf(fp, "+"); }
    if (getAVLVALUEbalance(w) == -1) { fprintf(fp, "-"); }
    }

void afree(void *v)
    {
    AVLVALUE *w = v;
    if (w->free != NULL) { w->free(getAVLVALUEvalue(w)); }
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
            //printf("---NOT IN TREE\n");                        
            AVLVALUE *new = newAVLVALUE(value, a->display, a->compare, a->free);
            BSTNODE *inserted = insertBST(a->tree, new); 
            a->size += 1;
            insertionFixup(a->tree, inserted);
            }
        else  // node value exists in tree
            {
            //printf("---IN TREE\n"); 
            setAVLVALUEcount(temp, getAVLVALUEcount(temp) + 1);
            a->size += 1;
            }
        }
    }


//This method returns the frequency of the searched-for value. If the value is not in the tree, the method should return zero. 
int findAVLcount(AVL *a, void *value)
    {
    AVLVALUE *temp = findAVLVALUE(a, value);
    if (temp == 0) { return 0; }
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


void *deleteAVL(AVL *a, void *value) //??FIX THIS
    {
    assert(a != 0);
    AVLVALUE *temp = findAVLVALUE(a, value);

    if (temp == 0) //value not in tree
        {
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
        BSTNODE *swapped = swapToLeafBST(a->tree, deleted);
        AVLVALUE *swap = getBSTNODEvalue(swapped);
        void *val = getAVLVALUEvalue(swap);

        deletionFixup(a->tree, swapped);
        pruneLeafBST(a->tree, swapped);
        
        a->size -= 1;
        setBSTsize(a->tree, sizeBST(a->tree) - 1);
        freeBSTNODE(swapped, freeAVLVALUE);
        return val;
        }
    
    }


int sizeAVL(AVL *a)
    {
    return sizeBST(a->tree);
    }


int duplicatesAVL(AVL *a)
    {
    return a->size - sizeBST(a->tree);
    }


void statisticsAVL(AVL *a, FILE *fp)
    {
    fprintf(fp, "Duplicates: %d\n", duplicatesAVL(a));
    
    statisticsBST(a->tree, fp);
    }

//The method calls the tree using a level-order traversal via decorated display of the underlying structure
void displayAVL(AVL *a, FILE *fp)
    {
    if (sizeAVL(a) == 0) { fprintf(fp, "EMPTY\n"); }

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
    freeAVLVALUE(find);
    if (temp == 0) { return 0; }
    
    AVLVALUE *found = getBSTNODEvalue(temp);
    return found;
    }


void insertionFixup(BST *t, BSTNODE *n)
    {
    while(1)
        {
        BSTNODE *par = getBSTNODEparent(n);
        if (n == par) 
            {
            setBSTroot(t, n);
            return;
            }

        AVLVALUE *p = getBSTNODEvalue(par);
        
        if ((getBSTNODEleft(par) == n && getAVLVALUEbalance(p) == -1) ||(getBSTNODEright(par) == n && getAVLVALUEbalance(p) == 1)) //parent favors the sibling
            {
            updateBalance(par);
            return;
            }
        else if (getAVLVALUEbalance(p) == 0) //parent has no fav
            {
            updateBalance(par);
            n = par; 
            continue;
            }
        else
            {// p is parent, y is fav of n
            BSTNODE *y = favorite(n);

            if (y != 0 && linear(y, n, par) == 0) //y exists and y,n,p are not linear
                {
                if (getBSTNODEleft(par) == n) //right left rotation
                    {
                    leftRotate(t, y); //rotate y to par
                    rightRotate(t, y); //rotate y to n
                    }
                else //left right rotation
                    {
                    rightRotate(t, y); //rotate y to par
                    leftRotate(t, y); //rotate y to n
                    }
                updateBalance(n);
                updateBalance(par);
                updateBalance(y);
                }
            else                                   //case 4
                {
                if (getBSTNODEleft(par) == n) //rotate right
                    {
                    rightRotate(t, n); //n to p
                    }
                else //rotate left
                    {
                    leftRotate(t, n); //n to p
                    }
                updateBalance(par);
                updateBalance(n);
                }
            return;
            }
        }
    }

void deletionFixup(BST *t, BSTNODE *n) //TODO FIX UP
    {
    AVLVALUE *x = getBSTNODEvalue(n);
    setAVLVALUEheight(x, -1);
    while(1)
        {
        BSTNODE *par = getBSTNODEparent(n);
        if (par == n) 
            {
            setBSTroot(t, n);
            break;
            }

        BSTNODE *sib = sibling(n);
        AVLVALUE *p = getBSTNODEvalue(par);

        if ((getBSTNODEright(par) == n && getAVLVALUEbalance(p) == -1) ||(getBSTNODEleft(par) == n && getAVLVALUEbalance(p) == 1))  //parent favors n
            {
            updateBalance(par);
            n = par;
            continue;
            }
        if (getAVLVALUEbalance(p) == 0)  //parent has no favorite
            {
            updateBalance(par);
            break;
            }
        else 
            { // p is parent, sib is sibiling, y is fav of sib
            BSTNODE *y = favorite(sib);

            if (y != 0 && linear(y, sib, par) == 0) //y exists and y,sib,par are not linear
                {
                
                if (getBSTNODEleft(par) == sib) //left right rotate
                    {
                    leftRotate(t, y); // rotate y to sib
                    rightRotate(t, y); //rotate y to par
                    }
                else //right left rotate
                    {
                    rightRotate(t, y); // rotate y to sib 
                    leftRotate(t, y); //rotate y to par
                    }
                updateBalance(sib);
                updateBalance(par);
                updateBalance(y);
                n = y;
                continue;
                }
            else
                {
                if (getBSTNODEleft(par) == sib) //rotate right
                    {
                    rightRotate(t, sib); //rotate sib to p
                    }
                else //rotate left
                    {
                    leftRotate(t, sib); //rotate sib to p
                    }    

                updateBalance(par); // set the balance of p
                updateBalance(sib); // set the balance of sib
                if (y == 0) break;
                n = sib;
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
    if (l == 0) { setAVLVALUElHeight(a, 0);}
    else
        {
        AVLVALUE *left = getBSTNODEvalue(l);
        setAVLVALUElHeight(a, getAVLVALUEheight(left)+1);
        }
    //printf("Left height = %d\n", getAVLVALUElHeight(a));

    //set n's right height
    if (r == 0) { setAVLVALUErHeight(a, 0);}
    else 
        {
        AVLVALUE *right = getBSTNODEvalue(r);
        setAVLVALUErHeight(a, getAVLVALUEheight(right)+1);
        }
    //printf("right height = %d\n", getAVLVALUErHeight(a));
    
    //set n's height to max +1
    if (getAVLVALUElHeight(a) > getAVLVALUErHeight(a)) { setAVLVALUEheight(a, getAVLVALUElHeight(a)); }
    else setAVLVALUEheight(a, getAVLVALUErHeight(a));

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

void rightRotate(BST *t, BSTNODE *n)
    {
    BSTNODE *p = getBSTNODEparent(n);
    BSTNODE *rightChild = getBSTNODEright(n);
    BSTNODE *gp = getBSTNODEparent(p);

    if (rightChild == 0) { setBSTNODEleft(p, 0); }
    else 
        { 
        setBSTNODEleft(p, rightChild);
        setBSTNODEparent(rightChild, p);
        }

    setBSTNODEright(n, p);

    if (gp == p) 
        { 
        setBSTNODEparent(n, n); 
        setBSTroot(t, n);
        }
    else
        { 
            if (getBSTNODEleft(gp) == p) { setBSTNODEleft(gp, n); }
            else { setBSTNODEright(gp, n); }
            setBSTNODEparent(n, gp);
        }
    
    setBSTNODEparent(p, n);
    setBSTNODEright(n, p);
    }

void leftRotate(BST *t, BSTNODE *n)
    {
    BSTNODE *p = getBSTNODEparent(n);
    BSTNODE *leftChild = getBSTNODEleft(n);
    BSTNODE *gp = getBSTNODEparent(p);  

    if (leftChild == 0) { setBSTNODEright(p, 0); }
    else 
        {
        setBSTNODEright(p, leftChild); 
        setBSTNODEparent(leftChild, p);
        }

    setBSTNODEleft(n, p);

    if (gp == p) 
        {
        setBSTNODEparent(n, n);
        setBSTroot(t, n);
        }
    else
        { 
            if (getBSTNODEleft(gp) == p) { setBSTNODEleft(gp, n); }
            else { setBSTNODEright(gp, n); }
            setBSTNODEparent(n, gp);
        }
    
    setBSTNODEparent(p, n);
    setBSTNODEleft(n, p);
    }

void freeAVLVALUE(void *a)
    {
    free(a);
    }
#include <stdio.h>


#include "avl.h"
#include "bst.h"

static void updateBalance(BSTNODE *n);
static void insertionFixup(BSTNODE *n);
static BSTNODE* sibling(BSTNODE *n);


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
    n->balance = 0;
    n->display = d;
    n->compare = c;
    n->free = f;

    return n;
    }

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

void adisplay(BSTNODE *n, FILE *fp)
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
    if (sizeAVL(g) == 0) //first node in empty-tree; 
        { 
            AVLVALUE *new = newAVLVALUE(value, a->display, a->compare, a->free);
            insertBST(a->tree, new); 
            a->size += 1;
        }
    else 
        {
        AVLVALUE *temp = findAVL(a, value);
        if (temp == NULL) //node value does not exist in tree;
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
    AVLVALUE *temp = findAVL(a, value);
    return getAVLVALUEcount(temp);
    }


//This method returns the searched-for value. If the value is not in the tree, the method should return NULL. 
void *findAVL(AVL *a, void *value)
    {
    assert(a != 0);

    AVLVALUE *find = newAVLVALUE(value, a->display, a->compare, a->free);
    BSTNODE *temp = findBST(a->tree, find);

    if (temp == 0) { return 0; }
    
    AVLVALUE *found = getBSTNODEvalue(temp);
    free(find);
    return found;
    }


void *deleteAVL(AVL *a, void *value)
    {
    assert(g != 0);
    AVLVALUE *temp = findAVL(a, value);

    if (temp == 0) { return 0; } //value not in tree
    
    else if (getAVLVALUEcount(temp) > 1) //node has duplicates
        {
        setAVLVALUEcount(temp, getAVLVALUEcount(temp) - 1);
        a->size -= 1;
        return temp;
        }
    else //node has no duplicates
        {
        BSTNODE *deleted = deleteBST(a->tree, temp);
        a->size -= 1;
        insertionFixup(getBSTNODEparent(deleted));
        return getBSTNODEvalue(deleted);
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
void insertionFixup(BSTNODE *n)
    {
    //TODO: translate pseudo code;
//      loop
            {
            BSTNODE *par = getBSTNODEparent(x);
            if (par == NULL) break;

            BSTNODE *sib = sibling(x);
            AVLVALUE *sibVal = getBSTNODEvalue(sib);
            AVLVALUE *xVal = getBSTNODEvalue(x);
            else if (getAVLVALUEheight(sib) > getAVLVALUEheight(x))       //case 1
                {
                updateBalance(par);
                break;
                }
            else if (parent is balanced)               //case 2
                {
                updateBalance(par);
                x = par;
                continue;
                }
//             else
//                 {
//                 y = the favorite child of x
//                 p = parent of x
//                 if (y exists and y,x,p are not linear) //case 3
//                     {
//                     rotate y to x
//                     rotate y to p
//                     set the balance of x
//                     set the balance of p
//                     set the balance of y
//                     }
//                 else                                   //case 4
//                     {
//                     rotate x to p
//                     set the balance of p
//                     set the balance of x
//                     }
//                 break;
//                 }
//             }
//         }
    }

void updateBalance(BSTNODE *n)
    {
    BSTNODE *l = getBSTNODEleft(n);
    BSTNODE *r = getBSTNODEright(n);
    
    AVLVALUE *a = getBSTNODEvalue(n);
    AVLVALUE *left = getBSTNODEvalue(l);
    AVLVALUE *right = getBSTNODEvalue(r);

    //set n's left height
    if (left == 0) { setAVLVALUElHeight(a, 0); }
    else setAVLVALUElHeight(a, getAVLVALUEheight(left));
    
    //set n's right height
    if (right == 0) { setAVLVALUErHeight(a, 0); }
    else setAVLVALUErHeight(a, getAVLVALUEheight(right));
    
    //set n's height to max +1
    if (getAVLVALUElHeight(a) > getAVLVALUErHeight(a)) { setAVLVALUEheight(a, getAVLVALUElHeight(a) + 1); }
    else setAVLVALUEheight(a, getAVLVALUErHeight(a) + 1) }

    setAVLVALUEbalance(a);
    }

BSTNODE* sibling(BSTNODE *n)
    {
    BSTNODE *temp = getBSTNODEparent(n);
    if (temp == 0) { return 0; }
    
    if (getBSTNODEleft(temp) == n) { return getBSTNODEright(temp); }
    if (getBSTNODEright(temp) == n) { return getBSTNODEleft(temp); }
    }
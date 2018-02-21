#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bst.h"
#include "queue.h"

//helper functions
static int isLeaf(BSTNODE *n);
static void printPreOrder(BST *t, BSTNODE *n, FILE *fp);
static void swap(BSTNODE *n, BSTNODE *r);
static int maxHeight(BSTNODE* n);
static int minHeight(BSTNODE* n);
static void deletePostOrder(BST *t, BSTNODE *n);

struct bstnode
    {
    BSTNODE *value;
    BSTNODE *left;
    BSTNODE *right;
    BSTNODE *parent;
    };

BSTNODE *newBSTNODE(void *v)
    {
    BSTNODE *n = malloc(sizeof(BSTNODE));
    assert (n != 0);

    n->value = v;
    n->left = 0;
    n->right = 0;
    n->parent = 0;
    return n;
    }

//accessors
void *getBSTNODEvalue(BSTNODE *n)
    {
    void *val = n->value;
    return val;
    }
BSTNODE *getBSTNODEleft(BSTNODE *n) { return n->left; }
BSTNODE *getBSTNODEright(BSTNODE *n) { return n->right; }
BSTNODE *getBSTNODEparent(BSTNODE *n) { return n->parent; }

//mutators
void setBSTNODEvalue(BSTNODE *n,void *value) { n->value = value; }
void setBSTNODEleft(BSTNODE *n,BSTNODE *replacement) { n->left = replacement; }
void setBSTNODEright(BSTNODE *n,BSTNODE *replacement) { n->right = replacement; }
void setBSTNODEparent(BSTNODE *n,BSTNODE *replacement) { n->parent = replacement; }

void freeBSTNODE(BSTNODE *n,void (*free)(void *))
    {
        if(free != NULL) { free(n->value); } //frees the node's value if the free function is not null
        free(n);
    }


struct bst 
    {
    BSTNODE *root;
    int size;
    void (*display)();
    void (*swapper)();
    int (*compare)();
    void (*free)();
    };    


BST *newBST(
    void (*d)(void *,FILE *),           //display
    int (*c)(void *,void *),            //comparator
    void (*s)(BSTNODE *,BSTNODE *),     //swapper
    void (*f)(void *))                 //free
    {
        BST *tree = malloc(sizeof(BST));
        assert(tree != 0);
        
        tree->root = 0;
        tree->size = 0;
        tree->display = d;
        tree->free = f;
        tree->compare = c;
        if (s != NULL) { tree->swapper = s; }
        else { tree->swapper = swap; }; //my own swap function
        return tree;
    }

//accessor
BSTNODE *getBSTroot(BST *t) { return t->root; }

//mutators
void setBSTroot(BST *t,BSTNODE *replacement) { t->root = replacement; }
void setBSTsize(BST *t,int s) { t->size = s; }

BSTNODE *insertBST(BST *t,void *value)
    {
    assert(t != 0);

    BSTNODE *temp = 0;
    temp = t->root;
    
    if (temp == 0)
        {
        BSTNODE *inserted = newBSTNODE(value);
        setBSTNODEleft(inserted, 0);
        setBSTNODEright(inserted, 0);
        setBSTNODEparent(inserted, 0);
        t->root = inserted;
        t->size++;
        return inserted;
        }
    else
        {
        void *oldVal = 0;
        while(temp != 0)
            {
            oldVal = getBSTNODEvalue(temp);
            if (t->compare(oldVal, value) >= 0 )
                {
                if (getBSTNODEleft(temp) == 0) { break; }
                temp = getBSTNODEleft(temp); 
                }
            else 
                {
                if (getBSTNODEright(temp) == 0) { break; }
                temp = getBSTNODEright(temp); 
                }
            }
        
        BSTNODE *inserted = newBSTNODE(value);

        if(t->compare(oldVal, value) >= 0 ) { setBSTNODEleft(temp, inserted); }
        else {setBSTNODEright(temp, inserted); }
        
        setBSTNODEparent(inserted, temp);
        t->size++;
        return inserted;
        }
    }

// This method returns the node that holds the searched-for value. If the value is not in the tree, 
// the method should return null. 
BSTNODE *findBST(BST *t,void *value)
    {
    BSTNODE *temp = 0;
    temp = t->root;
    if (t->size == 0) { return NULL; }
    while (t->compare(getBSTNODEvalue(temp), value) != 0)
        {
        if (temp == 0) { return 0; }
        if (t->compare(getBSTNODEvalue(temp), value) > 0) 
            { 
            if (getBSTNODEleft(temp) == 0) { return NULL; }
            temp = getBSTNODEleft(temp);
            }
        else 
            {
            if (getBSTNODEright(temp) == 0) { return NULL; }
            temp = getBSTNODEright(temp);
            }
        }

    return temp;
    }

BSTNODE *deleteBST(BST *t,void *value)
    {
        BSTNODE *temp = 0;
        BSTNODE *pruned = 0;
        temp = findBST(t, value);
        if (temp == 0) {return temp; }
        pruned = swapToLeafBST(t, temp);
        temp = pruned;
        pruneLeafBST(t,temp);
        t->size--;
        return pruned;
    }

BSTNODE *swapToLeafBST(BST *t,BSTNODE *node)
    {
    BSTNODE *next = 0;
    if (isLeaf(node)) { return node; }
    else 
        { //finds successor
        if (getBSTNODEright(node) !=0) 
            {
            next = getBSTNODEright(node); 
            while (next->left != 0) { next = getBSTNODEleft(next); }
            }
        else // if no successor finds predecessor
            {
            next = getBSTNODEleft(node);
            while(next->right != 0) { next = getBSTNODEright(next); }    
            }
        t->swapper(node, next);
        return swapToLeafBST(t, next); 
        }
    }

void pruneLeafBST(BST *t,BSTNODE *leaf)
    {
    BSTNODE *parent = 0;
    parent = getBSTNODEparent(leaf);

    if (parent == 0 ) 
        {
        if (leaf == t->root) { t->root = 0; }
        return; 
        }

    if (getBSTNODEleft(parent) == leaf) { setBSTNODEleft(parent, 0); }
    if (getBSTNODEright(parent) == leaf) { setBSTNODEright(parent, 0); }
    }

int sizeBST(BST *t)
    {
    return t->size;
    }

void statisticsBST(BST *t,FILE *fp)
    {
    int numNodes = 0;
    int minDepth = 0;
    int maxDepth = 0;

    numNodes = sizeBST(t);
    minDepth = minHeight(t->root);
    maxDepth = maxHeight(t->root);

    fprintf(fp, "Nodes: %d\n", numNodes);
    fprintf(fp, "Minimum depth: %d\n", minDepth);
    fprintf(fp, "Maximum depth: %d\n", maxDepth);
    }

void displayBST(BST *t,FILE *fp)
    {
    BSTNODE *temp = 0;
    temp = t->root;

    if (temp == 0) { fprintf(fp, "[]"); }
    printPreOrder(t, temp, fp);
    }

void displayBSTdebug(BST *t,FILE *fp)
    {
    if(t->root == 0) { return; }
    QUEUE *Q1 = newQUEUE(0, 0);
    QUEUE *Q2 = newQUEUE(0,0);
    enqueue(Q1, t->root);

    while(sizeQUEUE(Q1) != 0 || sizeQUEUE(Q2) != 0)
        {
        while(sizeQUEUE(Q1) != 0)
            {
            BSTNODE *current = peekQUEUE(Q1);
            if(getBSTNODEleft(current) != 0) { enqueue(Q2, getBSTNODEleft(current)); }
            if(getBSTNODEright(current) != 0) { enqueue(Q2, getBSTNODEright(current)); }
            t->display(getBSTNODEvalue(current), fp);
            if (sizeQUEUE(Q1) > 1) { fprintf(fp, " "); }
            dequeue(Q1);
            }
        fprintf(fp, "\n");
        if (sizeQUEUE(Q2) == 0) { break; }
        while(sizeQUEUE(Q2) != 0)
            {
            BSTNODE *second = peekQUEUE(Q2); 
            if(getBSTNODEleft(second) != 0) { enqueue(Q1, getBSTNODEleft(second)); }
            if(getBSTNODEright(second) != 0) { enqueue(Q1, getBSTNODEright(second)); }
            t->display(getBSTNODEvalue(second), fp);
            if (sizeQUEUE(Q2) > 1) { fprintf(fp, " "); }
            dequeue(Q2);
            }
        fprintf(fp, "\n");
        }
    freeQUEUE(Q1);
    freeQUEUE(Q2);
    }

//This method walks through the tree, freeing the nodes that make up the tree. Then, the tree object itself is freed. 
void freeBST(BST *t)
    {
    deletePostOrder(t, t->root);
    free(t);
    }


//helper function definitions
int isLeaf(BSTNODE *n)
    {
    if (getBSTNODEleft(n) == 0 && getBSTNODEright(n) == 0) { return 1; }
    else return 0;
    }

void printPreOrder(BST *t, BSTNODE *n, FILE *fp)
    {//maybe add separate helper functions for brackets
    if (n == 0) { return; }

    if (getBSTNODEparent(n) != 0) { fprintf(fp, " "); }
    fprintf(fp, "[");
    t->display(getBSTNODEvalue(n), fp);

    if (getBSTNODEleft(n) != 0) { printPreOrder(t, getBSTNODEleft(n), fp); }
    if (getBSTNODEright(n) != 0) { printPreOrder(t, getBSTNODEright(n), fp); }
    
    fprintf(fp, "]");
    }

void swap(BSTNODE *n, BSTNODE *r)
    {
    void *val = 0;
    void *valTwo = 0;
    val = getBSTNODEvalue(n);
    valTwo = getBSTNODEvalue(r);

    setBSTNODEvalue(n, valTwo);
    setBSTNODEvalue(r, val);
    }

int maxHeight(BSTNODE* n)
    {
    if (n==0) { return -1; }
    else
        {
        // compute the height of each subtree
        int lheight = maxHeight(getBSTNODEleft(n));
        int rheight = maxHeight(getBSTNODEright(n));
        
        if (lheight > rheight) { return(lheight+1); }
        else { return(rheight+1); }
        }
    
    }

int minHeight(BSTNODE* n)
    {
    if (n==0) { return -1; }
    else
        {
        // compute the height of each subtree
    
        int lheight = minHeight(getBSTNODEleft(n));
        int rheight = minHeight(getBSTNODEright(n));
 
        if (lheight < rheight) { return(lheight+1); }
        else { return(rheight+1); }
        }
    }

void deletePostOrder(BST *t, BSTNODE *n)
    {
    if (n == 0) { return; }

    deletePostOrder(t, getBSTNODEleft(n));

    deletePostOrder(t, getBSTNODEright(n));

    freeBSTNODE(n, t->free);
    }
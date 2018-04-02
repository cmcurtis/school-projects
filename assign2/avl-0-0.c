#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "queue.h"
#include "bst.h"
#include "avl.h"

void srandom(unsigned int);
long int random(void);

int
main(void)
    {
    srandom(1);
    //simple INTEGER test of AVL
    AVL *p = newAVL(displayINTEGER,compareINTEGER,freeINTEGER);
    insertAVL(p,newINTEGER(0));
    printf("AVL:\n");
    displayAVL(p,stdout);
    insertAVL(p,newINTEGER(1));
    printf("AVL:\n");
    displayAVL(p,stdout);
    insertAVL(p,newINTEGER(2));
    printf("AVL:\n");
    displayAVL(p,stdout);
    insertAVL(p,newINTEGER(3));
    printf("AVL:\n");
    displayAVL(p,stdout);
    insertAVL(p,newINTEGER(4));
    printf("AVL:\n");
    displayAVL(p,stdout);
    insertAVL(p,newINTEGER(5));
    statisticsAVL(p,stdout);
    printf("AVL:\n");
    displayAVL(p,stdout);
    printf("debug: ");
    displayAVLdebug(p,stdout);
    printf("\n");
    deleteAVL(p,newINTEGER(5));
    printf("AVL:\n");
    displayAVL(p,stdout);
    deleteAVL(p,newINTEGER(4));
    printf("AVL:\n");
    displayAVL(p,stdout);
    deleteAVL(p,newINTEGER(3));
    printf("AVL:\n");
    displayAVL(p,stdout);
    deleteAVL(p,newINTEGER(2));
    printf("AVL:\n");
    displayAVL(p,stdout);
    deleteAVL(p,newINTEGER(1));
    printf("AVL:\n");
    displayAVL(p,stdout);
    deleteAVL(p,newINTEGER(0));
    printf("AVL:\n");
    displayAVL(p,stdout);
    freeAVL(p);
    return 0;
    }

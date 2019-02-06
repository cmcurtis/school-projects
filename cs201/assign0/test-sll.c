#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

int
main(void)
    {
    srand(1);
    SLL *p = newSLL(displayINTEGER,freeINTEGER);
    insertSLL(p,0,newINTEGER(3));
    insertSLL(p,sizeSLL(p),newINTEGER(2));
    displaySLL(p,stdout);
    printf("\n");
    freeINTEGER(removeSLL(p,1));
    displaySLL(p,stdout);
    printf("\n");
    freeINTEGER(removeSLL(p,0));
    displaySLL(p,stdout);
    printf("\n");
    SLL *q = newSLL(displayINTEGER,freeINTEGER);
    insertSLL(p,0,newINTEGER(6));
    insertSLL(p,0,newINTEGER(7));
    insertSLL(q,0,newINTEGER(4));
    insertSLL(q,0,newINTEGER(5));
    displaySLL(p,stdout);
    printf("\n");
    //INTEGER* val = getSLL(p,1);
    //displayINTEGER(val,stdout);
    displaySLL(q,stdout);
    printf("\n");
    unionSLL(p,q);
    displaySLL(p,stdout);
    displaySLL(q,stdout);
    printf("\n");
    displaySLLdebug(p,stdout);
    printf("\n");
    displaySLLdebug(q,stdout);
    printf("\n");
    freeSLL(p);
    freeSLL(q);
    return 0;
    }
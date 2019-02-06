#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "integer.h"
#include "real.h"
#include "string.h"
#include "queue.h"
#include "gst.h"

void srandom(unsigned int);
long int random(void);

int
main(void)
    {
    srandom(4);
    //simple INTEGER test of BST
    int i;
    GST *p = newGST(displayINTEGER,compareINTEGER, freeINTEGER);
    for (i = 0; i < 11; ++i)
        {
        int j = random() % 11;
        INTEGER *a = newINTEGER(j);
        insertGST(p,a);
        }
    if (sizeGST(p) < 200)
        {
        printf("Display: ");
        displayGST(p,stdout);
        printf("\n");
        printf("Debug: ");
        displayGSTdebug(p,stdout);
        }
    //INTEGER *b = 9;
    //printf("count of 9 is %d\n",findGSTcount(p, b));
    printf("size is %d\n",sizeGST(p));
    statisticsGST(p,stdout);

    // freeBSTNODE(deleteGST()) // delete a value
    // if (sizeGST(p) < 200)
    //     {
    //     printf("Display: ");
    //     displayGST(p,stdout);
    //     printf("\n");
    //     printf("Debug: ");
    //     displayGSTdebug(p,stdout);
    //     }
    printf("size is %d\n",sizeGST(p));
    statisticsGST(p,stdout);
    freeGST(p);
    return 0;
    }
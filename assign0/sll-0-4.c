#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "integer.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(5);
    SLL *p = newSLL(displayINTEGER,freeINTEGER);
    int i;
    for (i = 0; i < 15; ++i)
        {
        int j = random() % 100;
        insertSLL(p,0,newINTEGER(j));
        }
    if (sizeSLL(p) < 100)
        {
        displaySLL(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeSLL(p));
    printf("value at 5 is %d\n",getINTEGER(getSLL(p,5)));
    printf("setting value at 5 to 10\n");
    freeINTEGER(setSLL(p,5,newINTEGER(10)));
    printf("value at 5 now is %d\n",getINTEGER(getSLL(p,5)));
    freeSLL(p);
    return 0;
    }

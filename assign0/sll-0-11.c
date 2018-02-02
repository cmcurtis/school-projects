#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "real.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(12);
    SLL *p = newSLL(displayREAL,freeREAL);
    int i;
    for (i = 0; i < 10000; ++i)
        {
        int j = random() % 100;
        int k = random() % (sizeSLL(p) + 1);
        j += (random() % 100) / 100.0;
        insertSLL(p,k,newREAL(j));
        }
    if (sizeSLL(p) < 100)
        {
        displaySLL(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeSLL(p));
    printf("value at 3760 is %.2lf\n",getREAL(getSLL(p,3760)));
    printf("setting value at 3760 to 14.94\n");
    freeREAL(setSLL(p,3760,newREAL(14.94)));
    printf("value at 3760 now is %.2lf\n",getREAL(getSLL(p,3760)));
    freeSLL(p);
    return 0;
    }

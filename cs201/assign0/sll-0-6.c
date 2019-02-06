#include <stdio.h>
#include <stdlib.h>
#include "sll.h"
#include "real.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(7);
    SLL *p = newSLL(displayREAL,freeREAL);
    int i;
    for (i = 0; i < 37; ++i)
        {
        int j = random() % 100;
        int k = random() % (sizeSLL(p) + 1);
        j += (random() % 100) / 100.0;
        insertSLL(p,k,newREAL(j));
        }
    freeREAL(removeSLL(p,12));
    freeREAL(removeSLL(p,29));
    freeREAL(removeSLL(p,31));
    freeREAL(removeSLL(p,10));
    freeREAL(removeSLL(p,29));
    freeREAL(removeSLL(p,3));
    insertSLL(p,9,newREAL(20.20));
    insertSLL(p,32,newREAL(70.70));
    insertSLL(p,28,newREAL(63.63));
    insertSLL(p,14,newREAL(49.49));
    insertSLL(p,1,newREAL(92.92));
    freeREAL(removeSLL(p,14));
    freeREAL(removeSLL(p,34));
    insertSLL(p,2,newREAL(6.6));
    freeREAL(removeSLL(p,32));
    insertSLL(p,23,newREAL(8.8));
    freeREAL(removeSLL(p,5));
    freeREAL(removeSLL(p,16));
    insertSLL(p,3,newREAL(0.0));
    freeREAL(removeSLL(p,23));
    insertSLL(p,1,newREAL(1.1));
    insertSLL(p,11,newREAL(5.5));
    freeREAL(removeSLL(p,12));
    insertSLL(p,10,newREAL(95.95));
    insertSLL(p,9,newREAL(29.29));
    insertSLL(p,34,newREAL(87.87));
    insertSLL(p,29,newREAL(83.83));
    freeREAL(removeSLL(p,29));
    freeREAL(removeSLL(p,2));
    freeREAL(removeSLL(p,17));
    freeREAL(removeSLL(p,11));
    insertSLL(p,20,newREAL(51.51));
    insertSLL(p,3,newREAL(4.4));
    insertSLL(p,3,newREAL(9.9));
    insertSLL(p,34,newREAL(27.27));
    insertSLL(p,6,newREAL(75.75));
    freeREAL(removeSLL(p,31));
    if (sizeSLL(p) < 100)
        {
        displaySLL(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeSLL(p));
    printf("value at 26 is %.2lf\n",getREAL(getSLL(p,26)));
    printf("setting value at 26 to 97.10\n");
    freeREAL(setSLL(p,26,newREAL(97.10)));
    printf("value at 26 now is %.2lf\n",getREAL(getSLL(p,26)));
    freeSLL(p);
    return 0;
    }

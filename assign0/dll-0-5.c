#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include "real.h"

extern void srandom(unsigned int);
extern long int random(void);

int
main(void)
    {
    srandom(6);
    DLL *p = newDLL(displayREAL,freeREAL);
    int i;
    for (i = 0; i < 11; ++i)
        {
        int j = random() % 100;
        int k = random() % (sizeDLL(p) + 1);
        j += (random() % 100) / 100.0;
        insertDLL(p,k,newREAL(j));
        }
    if (sizeDLL(p) < 100)
        {
        displayDLL(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeDLL(p));
    printf("value at 6 is %.2lf\n",getREAL(getDLL(p,6)));
    printf("setting value at 6 to 12.65\n");
    freeREAL(setDLL(p,6,newREAL(12.65)));
    printf("value at 6 now is %.2lf\n",getREAL(getDLL(p,6)));
    freeDLL(p);
    return 0;
    }

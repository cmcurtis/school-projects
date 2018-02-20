#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "real.h"

struct REAL
    {
    double value;
    };

REAL *
newREAL(double x)
    {
    REAL *p = malloc(sizeof(REAL));
    assert(p != 0);
    p->value = x;
    return p;
    }

double 
getREAL(REAL *v)
    {
    return v->value;
    }

double 
setREAL(REAL *v,double x)
    {
    double old = v->value;
    v->value = x;
    return old;
    }

void 
displayREAL(void *v,FILE *fp)
    {
    fprintf(fp,"%.6f",getREAL((REAL *) v));
    }

int 
compareREAL(void *v,void *w)
    {
    double d = getREAL(v) - getREAL(w);
    if (d > 0)
        d = d + 0.5;
    else if (d < 0)
        d = d - 0.5;
    int y = (int)d;

    return y;
    }
int 
compareREALdecr(void *v,void *w)
    {
    double d = getREAL(w) - getREAL(v);
    if (d > 0)
        d = d + 0.5;
    else if (d < 0)
        d = d - 0.5;
    int y = (int)d;

    return y;
    }


void
freeREAL(void *v)
    {
    free((REAL *) v);
    }

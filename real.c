///////////////////////////////////////////
///                                     ///
///    real.c for CS201 assignment 1    ///
///                                     ///
///   Dakota Turner February 2017       ///
///                                     ///
///      a real class, implemented in   ///
///      sqsort.c                       ///
///                                     ///
///////////////////////////////////////////


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "real.h"

real *
newReal(double x)
  {
  real *p = malloc(sizeof(real));
  //if (p == 0) Fatal("out of memory\n");
  p->value = x;
  return p;
  }
  
double 
getReal(real *v)
    {
    return v->value;
    }

double
setReal(real *v,double x)
    {
    double old = v->value;
    v->value = x;
    return old;
    }

void 
displayReal(FILE *fp,void *v)
    {
    fprintf(fp,"%f",getReal(v));
    }
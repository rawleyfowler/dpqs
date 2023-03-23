#ifndef DPQS_H
#define DPQS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/types.h>

#define QUICKSORT_THRESH 286
#define INSERTION_THRESH 27
#define dbl_t double

void dpqs_sort(dbl_t[], u_int64_t, u_int64_t);

#endif

/**
  Permission is hereby granted, free of charge,
  to any person obtaining a copy of this software and associated documentation files (the “Software”),
  to deal in the Software without restriction,
  including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "dpqs.h"
#include <sys/types.h>

void swap(int64_t a[], u_int64_t i, u_int64_t j) {
  int64_t tmp = a[i];
  a[i] = a[j];
  a[j] = tmp;
}

/**
 * Using Hoare's partition scheme
 */
u_int64_t dpqs_qs_partition(int64_t array[], u_int64_t lo, u_int64_t hi) {
  int64_t p = array[(int64_t) (floor((hi - lo) / 2.0) + lo)];

  u_int64_t i, j;
  for (i = lo, j = hi;; i++, j--) {
    while(array[i] < p)
      i++;
    
    while(array[j] > p)
      j--;

    if (i >= j)
      return j;

    swap(array, i, j);
  }

  return -1;
}

/**
 * Insertion sort without a sentinel (fast enough)
 */
void dpqs_insertion_sort(int64_t array[], u_int64_t lo, u_int64_t hi) {
  for (u_int64_t i = lo, j = i; i < hi; j = i++) {
    int64_t e = array[i + 1];
    while (e < array[j]) {
      array[j+1] = array[j];      
      if (j-- == lo)
        break;
    }
    array[j+1] = e;
  }
}

/**
 * Double pivot quicksort
 */
void dpqs_partition(int64_t array[], u_int64_t lo, u_int64_t hi, u_int64_t div) {
  u_int64_t len = (hi + 1) - lo;
  
  if (len < INSERTION_THRESH) {
    dpqs_insertion_sort(array, lo, hi);
    return;
  }
 
  u_int64_t thr = len / div;
  u_int64_t m1 = lo + thr, m2 = hi - thr;

  if (m1 <= lo)
    m1 = lo + 1;
  if (m2 >= hi)
    m2 = hi - 1;

  if (array[m1] < array[m2]) {
    swap(array, m1, lo);
    swap(array, m2, hi);
  } else {
    swap(array, m1, hi);
    swap(array, m2, lo);
  }

  int64_t p1 = array[lo], p2 = array[hi];

  u_int64_t less = lo + 1;
  u_int64_t more = hi - 1;
  for (u_int64_t i = lo + 1, j = hi - 1; i < more; i++) {
    if (array[i] < p1) {
      swap(array, i, less++);
    } else if (array[i] > p2) {
      while(i < more && array[more] > p2) {
        more--;
      }
      
      swap(array, i, more--);

      if (array[i] < p1)
        swap(array, i, less++);
    }
  }

  u_int64_t dist = more - less;
  if (dist < 13)
    thr++;

  swap(array, less - 1, lo);
  swap(array, more + 1, hi);

  if (dist > len - 13 && p1 != p2) {
    for (u_int64_t i = less; i <= more; i++) {
      if (array[i] == p1)
        swap(array, i, less++);
      else if (array[i] == p2) {
        swap(array, i, more--);

        if (array[i] == p2)
          swap(array, i, less++);
      }
    }
  }

  if (p1 < p2)
    dpqs_partition(array, less, more, div);
}

void dpqs_sort(int64_t array[], u_int64_t lo, u_int64_t hi) {
  if (lo >= hi ||
      hi < 0   ||
      lo < 0) {
    return;
  }

  u_int64_t p;
  u_int64_t elems = (hi - lo) - 1;
  if (elems < INSERTION_THRESH) {
    dpqs_insertion_sort(array, lo, hi);
    return;
  } else if (elems < QUICKSORT_THRESH) {
    p = dpqs_qs_partition(array, lo, hi);
  } else {
    dpqs_partition(array, lo, hi, 3);
    return;
  }
  
  dpqs_sort(array, lo, p);
  dpqs_sort(array, p + 1, hi);
}

int main() {
  int64_t i[9999];

  for (size_t j = 0; j < 9999; j++) {
    i[j] = (int64_t) rand() / 1000000;
  }

  dpqs_sort(i, 0, 9998);

  for (size_t j = 0; j < 9999; j++) {
    printf("%ld ", i[j]);

    if (j % 10 == 0 && j > 0)
      printf("\n");
  }
}

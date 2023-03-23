/**
  Permission is hereby granted, free of charge,
  to any person obtaining a copy of this software and associated documentation
  files (the “Software”), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to permit
  persons to whom the Software is furnished to do so, subject to the following
  conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
  OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
  OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "dpqs.h"
#include <stdint.h>
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
  int64_t p = array[(int64_t)((hi - lo) >> 1) + lo];

  u_int64_t i, j;
  for (i = lo, j = hi;; i++, j--) {
    while (array[i] < p)
      i++;

    while (array[j] > p)
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
      array[j + 1] = array[j];
      if (j-- == lo)
        break;
    }
    array[j + 1] = e;
  }
}

/**
 * Double pivot quicksort
 */
void dpqs_partition(int64_t array[], u_int64_t lo, u_int64_t hi) {
  if (hi <= lo)
    return;
  
  u_int64_t len = hi - lo;
  
  if (len < INSERTION_THRESH) {
    dpqs_insertion_sort(array, lo, hi);
    return;
  }

  if (array[lo] > array[hi])
    swap(array, lo, hi);

  int64_t p = array[lo], q = array[hi];

  u_int64_t lt = lo + 1, gt = hi - 1;
  u_int64_t l = lo + 1;
  while (l <= gt) {
    if (array[l] > array[lo])
      swap(array, lt++, l++);
    else if (array[hi] < array[l])
      swap(array, l, gt--);
    else
      l++;
  }

  swap(array, lo, --lt);
  swap(array, hi, ++gt);

  dpqs_partition(array, lo, lt - 1);
  if (array[lt] < array[gt])
    dpqs_partition(array, lt + 1, gt - 1);
  dpqs_partition(array, gt + 1, hi);
}

void dpqs_sort(int64_t array[], u_int64_t lo, u_int64_t hi) {
  if (lo >= hi || hi < 0 || lo < 0 || hi - lo < 2) {
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
    dpqs_partition(array, lo, hi);
    return;
  }

  dpqs_sort(array, lo, p);
  dpqs_sort(array, p + 1, hi);
}

int main() {
  int64_t i[9999];

  for (size_t j = 0; j < 9999; j++) {
    i[j] = (int64_t)rand() / 1000000;
  }

  dpqs_sort(i, 0, 9998);

  for (size_t j = 0; j < 9999; j++) {
    printf("%ld ", i[j]);

    if (j % 10 == 0 && j > 0)
      printf("\n");
  }
}

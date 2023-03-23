# Dual Pivot Quicksort
A version of quicksort originally deemed slower than traditional quicksort,
but [proven](https://codeblab.com/wp-content/uploads/2009/09/DualPivotQuicksort.pdf) by Vladimir Yaroslavskiy to
actually be faster than traditional quicksort on larger arrays, `n > 286`, so this implementation takes advantage
of this by using Insertion Sort, Quick Sort, and Dual Pivot Quick Sort to produce a very fast numeric sorting interface. This is the current sorting method used on the Java Virtual Machine (JVM) for sorting large arrays of primitive values (int, float, double, etc).

## How to use
```c
#include <dpqs.h>

int main(void) {
  int foo[2000];
  
  for (int i = 0; i < 2000; i++) {
    foo[i] = i + 39;
  }
  
  dpqs_sort(foo, 0, 1999);
  
  // Foo is sorted :)
}
```

## How The Algorithm Works
- Take in the array and bounds Lo and Hi
- For A with less than 27 elements, use Insertion sort
- For A with greater than 27 elements, and less than 286 elements, use Hoare's quicksort
- A[Lo] < A[Hi] or else swap them
- Choose 2 pivot elements
  - P = A[Lo]
  - Q = A[Hi]
- Assign three pointers:
  - L = location of P + 1
  - K = L
  - G = location of Q - 1
- While K is less than or equal to G
  - Swap A[K] with A[L] if A[K] < P, increment K, and L
  - Swap A[K] with G if A[K] > Q, decrement G
  - Otherwise, increment K
- Swap P with A[L + 1]
- Swap Q with A[G - 1]
- Increment L
- Decrement G
- Recursively sort the sub-array from Lo to L
- Recursively sort the sub-array from L + 1 to G if A[L] < A[G]
- Recursively sort the sub-array from G + 1 to Hi
- The array is sorted

## Credits

- Vladimir Yaroslavskiy (Dual-Pivot Quicksort algorithm)

## License
This implementation is available under the MIT License, more information is provided by the `LICENSE` 
file at the root of the project.

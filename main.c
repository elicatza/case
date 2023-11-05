#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define ARR_IMPLEMENTATION
#include "./arr.h"

// TODO: implmentations
// append (combine two arrs)
// with_capacity (init with user set cap)
// clear (reste array)
// equals (check equality according to qsort(3))
// remove (remove element at index, shifting all values to the left) O(n)
// resize (make len equal to new_len (takes fill value if new is greater))
// insert (set index to val, shifiting all values after to the right) O(n)
// get


int main(void)
{
    size_t i;
    size_t *arr = arr_init(3, sizeof(*arr));

    arr_push(arr, 69);
    arr_push(arr, 32);
    arr_push(arr, 34);
    arr_push(arr, 35);

    printf("[ ");
    for (i = 0; i < arr_len(arr); ++i) {
        printf("%zu ", arr[i]);
    }
    printf("]\n");
    printf("Pop %zu\n", arr_pop(arr));
    printf("Pop %zu\n", arr_pop(arr));
    printf("Pop %zu\n", arr_pop(arr));
    printf("Pop %zu\n", arr_pop(arr));
    arr_free(arr);
}

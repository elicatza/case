#include <stdio.h>

#define ARR_IMPLEMENTATION
#include "./arr.h"


int main(void)
{
    char *arr = arr_init(3, sizeof(*arr));

    arr_push(arr, 'H');
    arr_push(arr, 'e');
    arr_push(arr, 'l');
    arr_push(arr, 'l');
    arr_push(arr, 'o');

    char *world = arr_init(2, sizeof(*arr));

    arr_push(world, ',');
    arr_push(world, ' ');
    arr_push(world, 'w');
    arr_push(world, 'o');
    arr_push(world, 'r');
    arr_push(world, 'l');
    arr_push(world, 'd');

    arr_print(arr, "%c");
    arr_print(world, "%c");
    arr_append((void *) &arr, world);
    arr_print(arr, "%c");
    printf("Removed: %c\n", arr_remove(arr, 1));
    arr_print(arr, "%c");
    arr_insert(arr, 'e', 1);
    arr_print(arr, "%c");

    arr_free(arr);
    arr_free(world);
}

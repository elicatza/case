#include <stdio.h>

#define CASE_IMPLEMENTATION
#include "./case.h"


int main(void)
{
    char *arr = case_init(3, sizeof(*arr));

    case_push(arr, 'H');
    case_push(arr, 'e');
    case_push(arr, 'l');
    case_push(arr, 'l');
    case_push(arr, 'o');

    char *world = case_init(2, sizeof(*arr));

    case_push(world, ',');
    case_push(world, ' ');
    case_push(world, 'w');
    case_push(world, 'o');
    case_push(world, 'r');
    case_push(world, 'l');
    case_push(world, 'd');

    case_print(arr, "%c");
    case_print(world, "%c");
    case_append((void *) &arr, world);
    case_print(arr, "%c");
    printf("Removed: %c\n", case_remove(arr, 1));
    case_print(arr, "%c");
    case_insert(arr, 'e', 1);
    case_print(arr, "%c");

    case_free(arr);
    case_free(world);
}

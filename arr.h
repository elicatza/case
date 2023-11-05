#ifndef ARR_H
#define ARR_H

#include <stddef.h>


typedef struct ArrBase ArrBase;
struct ArrBase {
    size_t capacity;
    size_t len;
    size_t size;
};

#define GROW_FACTOR 2

#define FIELD_OFFSET(type, field) (unsigned long) &(((type *) 0)->field)
#define arr_cap(arr) *(size_t *) ((char *) (arr) - sizeof(ArrBase) + FIELD_OFFSET(ArrBase, capacity))
#define arr_len(arr) *(size_t *) ((char *) (arr) - sizeof(ArrBase) + FIELD_OFFSET(ArrBase, len))
#define arr_size(arr) *(size_t *) ((char *) (arr) - sizeof(ArrBase) + FIELD_OFFSET(ArrBase, size))
#define arr_base(arr) (*(ArrBase *) ((char *) (arr) - sizeof(ArrBase)))

#define arr_base_to_arr(base) ((char *) (base) + sizeof(ArrBase))
#define arr_pop(arr) (assert(arr_len(arr) > 0), --arr_len(arr), arr[arr_len(arr)])

#define arr_push(arr, item) \
    do { \
        if (arr_len(arr) >= arr_cap(arr)) { \
            _arr_grow((void *) &(arr)); \
        } \
        (arr)[arr_len((arr))] = (item); \
        ++arr_len(arr); \
    } while (0)


void *arr_init(size_t capacity, size_t item_size);
void arr_free(void *arr);

#endif // ARR_H
#ifdef ARR_IMPLEMENTATION

#include <assert.h>
#include <stdlib.h>

void *arr_init(size_t capacity, size_t item_size)
{
    void *base = malloc(item_size * capacity + sizeof(ArrBase));
    assert(base != NULL && "Malloc failed: buy more ram");
    void *arr = arr_base_to_arr(base);

    arr_len(arr) = 0;
    arr_cap(arr) = capacity;
    arr_size(arr) = item_size;
    return arr;
}


void _arr_grow(void **arr)
{
    arr_cap(*arr) *= GROW_FACTOR;
    void *mem = realloc(&arr_base(*arr), arr_size(*arr) * arr_cap(*arr) + sizeof(ArrBase));
    assert(mem != NULL && "ERROR: realloc failed. buy more ram");
    *arr = arr_base_to_arr(mem);
}

void arr_free(void *arr)
{
    free(&arr_base(arr));
}

#endif // ARR_IMPLEMENTATION

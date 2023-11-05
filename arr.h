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
#define arr_get(arr, i) (assert(i >= 0), assert(i < arr_len(arr)), arr[(i)])
#define arr_push(arr, item) \
    do { \
        if (arr_len(arr) >= arr_cap(arr)) { \
            arr_resize((void *) &(arr), arr_cap(arr) * GROW_FACTOR); \
        } \
        (arr)[arr_len((arr))] = (item); \
        ++arr_len(arr); \
    } while (0)

#define arr_remove(arr, idx) (arr_shift_left(arr, idx), arr_pop(arr))
#define arr_insert(arr, item, idx) do { arr_push(arr, item); arr_shift_right(arr, idx); } while (0)

#define arr_print(arr, fmt) \
    do { \
        size_t __i; \
        printf("%s = [ ", #arr); \
        for (__i = 0; __i < arr_len((arr)); ++__i) { \
            printf(fmt" ", (arr)[__i]); \
        } \
        printf("]\n"); \
    } while (0)

void *arr_init(size_t capacity, size_t item_size);
void arr_clear(void *arr);
void arr_resize(void **arr, size_t size);
void arr_append(void **dest, void *src);
void arr_shift_left(void *arr, size_t start);
void arr_shift_right(void *arr, size_t start);
void arr_free(void *arr);

#endif // ARR_H
#ifdef ARR_IMPLEMENTATION

#include <assert.h>
#include <stdlib.h>
#include <string.h>

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

void arr_resize(void **arr, size_t size)
{
    printf("Current cap: %zu\n", arr_cap(*arr));
    arr_cap(*arr) = size;
    void *mem = realloc(&arr_base(*arr), arr_size(*arr) * arr_cap(*arr) + sizeof(ArrBase));
    assert(mem != NULL && "ERROR: realloc failed. buy more ram");
    *arr = arr_base_to_arr(mem);

    printf("Changed cap: %zu\n", arr_cap(*arr));
}

void arr_append(void **dest, void *src)
{
    assert(arr_size(*dest) == arr_size(src));
    size_t new_len = arr_len(*dest) + arr_len(src);

    if (new_len > arr_cap(*dest)) {
        arr_resize(dest, new_len * GROW_FACTOR);
    }

    void *rv = memcpy((char *) *dest + arr_len(*dest) * arr_size(*dest), src, arr_len(src));
    assert(rv != NULL);
    arr_len(*dest) = new_len;
}

void arr_shift_left(void *arr, size_t start)
{
    long int diff = arr_len(arr) - start;
    assert(diff > 0);

    void *first = malloc(arr_size(arr));
    memcpy(first, (char *) arr + start * arr_size(arr), arr_size(arr));

    memmove((char *) arr + start * arr_size(arr), (char *) arr + (start + 1) * arr_size(arr), diff);

    memcpy((char *) arr + (arr_len(arr) - 1) * arr_size(arr), first, arr_size(arr));
    free(first);
}

void arr_shift_right(void *arr, size_t start)
{
    long int diff = arr_len(arr) - start;
    assert(diff > 0);

    void *last = malloc(arr_size(arr));
    memcpy(last, (char *) arr + (arr_len(arr) - 1) * arr_size(arr), arr_size(arr));

    memmove((char *) arr + (start + 1) * arr_size(arr), (char *) arr + start * arr_size(arr), diff);

    memcpy((char *) arr + start * arr_size(arr), last, arr_size(arr));
    free(last);
}

void arr_clear(void *arr)
{
    arr_len(arr) = 0;
}

void arr_free(void *arr)
{
    free(&arr_base(arr));
}

#endif // ARR_IMPLEMENTATION

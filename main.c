#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <assert.h>


typedef struct GenStruct GenStruct;
struct GenStruct {
    size_t *items;
    size_t capacity;
    size_t len;
};

typedef struct ArrPre ArrPre;
struct ArrPre {
    size_t capacity;
    size_t len;
    size_t size;
};


#define genarr_init(arr, cap) \
    _genarr_init((void *) &(arr), \
            (size_t) (cap), \
            sizeof((arr).items[0]), \
            (size_t) &(arr).capacity - (size_t) &(arr), \
            (size_t) &(arr).items - (size_t) &(arr), \
            (size_t) &(arr).len - (size_t) &(arr) \
            )


void _genarr_init(void *arr, size_t capacity, size_t item_size,
        size_t capacity_offset,
        size_t items_offset,
        size_t len_offset)
{
    size_t *len = (size_t *) ((char *) arr + len_offset);
    size_t *cap = (size_t *) ((char *) arr + capacity_offset);
    size_t *items = (size_t *) ((char *) arr + items_offset);
    *len = 0;
    *cap = capacity;

    void *base = malloc(item_size * capacity + sizeof(ArrPre));
    assert(base != NULL && "Malloc failed: buy more ram");
    *items = (size_t) (char *) base + sizeof(ArrPre);
    printf("base  addr %p\n", base);
    printf("items val  0x%lx\n", *items);

    ArrPre *base_arr = base;
    base_arr->len = 0;
    base_arr->capacity = capacity;
    base_arr->size = item_size;
    // printf("init cap: %zu\n", base_arr->capacity);
    // items[0] = 70;
    // printf("init item: %zu\n", items[0]);
    return;
}

void _genarr_free(void *arr, size_t items_offset)
{
    size_t *items = (size_t *) ((char *) arr - sizeof(ArrPre));
    printf("free       %p\n", (void *) *items);

    free((void *) *items);
    return;
}

#define genarr_free(arr) \
    _genarr_free((void *) &(arr), \
            (size_t) &(arr).items - (size_t) &(arr) \
            )


/* Check cstring for format: print format according to size */
void _genarr_print(void *arr,
        size_t items_offset, size_t item_size,
        size_t len_offset)
{
    size_t *len = (size_t *) ((char *) arr + len_offset);
    size_t *items = (size_t *) ((char *) arr + items_offset);

    printf("[ ");
    char *ptr;
    for (ptr = (void *) *items; ptr < (char *) *items + *len * item_size; ++ptr) {
        printf("%02hhX ", *ptr);
    }
    printf("]\n");

}

void _genarr_append_grow_if_needed(void *arr,
        size_t item_size,
        size_t capacity_offset,
        size_t items_offset,
        size_t len_offset)
{
    size_t *len = (size_t *) ((char *) arr + len_offset);
    size_t *cap = (size_t *) ((char *) arr + capacity_offset);

    *len += 1;
    if (*len <= *cap) {
        return;
    }

    size_t *items = (size_t *) ((char *) arr + items_offset);

    *cap *= 2;

    void *mem = realloc((void *) *items, item_size * *cap);
    *items = (size_t) mem;
    assert(items != NULL && "ERROR: realloc failed. buy more ram");
}

#define genarr_append_grow_if_needed(arr) \
    _genarr_append_grow_if_needed((void *) &(arr), \
            sizeof((arr).items[0]), \
            (size_t) &(arr).capacity - (size_t) &(arr), \
            (size_t) &(arr).items - (size_t) &(arr), \
            (size_t) &(arr).len - (size_t) &(arr) \
            )

#define genarr_append(arr, item) (genarr_append_grow_if_needed((arr)), (arr).items[(arr).len - 1] = (item))

#define genarr_print(arr) \
    _genarr_print((void *) &(arr), \
            (size_t) &(arr).items - (size_t) &(arr), \
            sizeof((arr).items[0]), \
            (size_t) &(arr).len - (size_t) &(arr));


int main(void)
{
    GenStruct arr;
    genarr_init(arr, (3));
    printf("main addr  %lx\n", *arr.items);
    // printf("Cap: %zu\n", arr.capacity);
    // char foo = 'A';
    //genarr_append(arr, 'C');
    // genarr_append_grow_if_needed(arr);
    // arr.items[arr.len - 1] = 'C';
    //genarr_append(arr, foo);
    // char bar = 'B';
    //genarr_append(arr, bar);
    // printf("Cap: %zu\n", arr.capacity);
    // genarr_print(arr);
    genarr_free(arr);
}

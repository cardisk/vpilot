#ifndef ARRAY_H_
#define ARRAY_H_

#include <stdlib.h>
#include <string.h>

//
// Usage Example:
//
// struct List
// {
//      int *ptr;
//      int length;
//      int capacity;
// };
//
// struct List list = {0};
//
// array_push(&list, 10);
// array_push(&list, 20);
// array_push(&list, 30);
//
// array_foreach(&list, int, number)
// {
//      printf("%d\n", number);
// }
//
// array_free(&list);

#define ARRAY_DEFAULT_CAPACITY 16

#define array_push(arr, item)                                               \
do                                                                          \
{                                                                           \
    if (!(arr)->ptr)                                                        \
        (arr)->ptr = malloc(ARRAY_DEFAULT_CAPACITY * sizeof(*(arr)->ptr));  \
                                                                            \
    if ((arr)->length >= (arr)->capacity)                                   \
        (arr)->ptr = realloc((arr)->ptr, (arr)->capacity * 2);              \
                                                                            \
    ((arr))->ptr[((arr))->length++] = (item);                               \
}                                                                           \
while(0)                                                

#define array_push_front(arr, item)                                         \
do                                                                          \
{                                                                           \
    if (!(arr)->ptr)                                                        \
        (arr)->ptr = malloc(ARRAY_DEFAULT_CAPACITY * sizeof(*(arr)->ptr));  \
                                                                            \
    if ((arr)->length >= (arr)->capacity)                                   \
        (arr)->ptr = realloc((arr)->ptr, (arr)->capacity * 2);              \
                                                                            \
    memmove((arr)->ptr[1], (arr)->ptr, (arr)->length);                      \
    (arr)->ptr[0] = item;                                                   \
    (arr)->length++;                                                        \
}                                                                           \
while(0)

#define array_foreach(arr, type, it_name) \
    for (type *it_name = (arr)->ptr; it_name < (arr)->ptr + (arr)->length; it_name++)

#define array_clear(arr) arr->length = 0
#define array_free(arr) (arr->ptr) ? free(arr->ptr) : 0

#endif // ARRAY_H_

#ifndef ARENA_H_
#define ARENA_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct Arena_
{
    size_t used;
    uint8_t *ptr;
};

typedef struct Arena_ Arena;

Arena arena_init(size_t capacity)
{
    Arena arena = {
        .used = 0,
        .ptr  = (uint8_t *) malloc(capacity),
    };

    return arena;
}

void *arena_alloc(Arena *arena, size_t size)
{
    void *ptr = &arena->ptr[arena->used];
    arena->used += size;
    return ptr;
}

void *arena_calloc(Arena *arena, size_t size)
{
    void *ptr = arena_alloc(arena, size);
    memset(ptr, 0, size);
    return ptr;
}

static inline void arena_clear(Arena *arena)
{
    arena->used = 0;
}

static inline void arena_free(Arena *arena)
{
    free(arena->ptr);
}

void *arena_copy_string(Arena *arena, const char *str)
{
    // Adding \0 inside the size
    int str_size = strlen(str) + 1;

    void *ptr = arena_calloc(arena, str_size);
    memcpy(ptr, str, str_size);

    return ptr;
}

#endif // ARENA_H_

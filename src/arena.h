#ifndef ARENA_H_
#define ARENA_H_

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
        .ptr  = malloc(capacity),
    };

    return arena;
}

void *arena_alloc(Arena *arena, size_t size)
{
    void *ptr = &arena->ptr[arena->used];
    arena->used += size;
    return ptr;
}

inline void arena_clear(Arena *arena)
{
    arena->used = 0;
}

inline void arena_free(Arena *arena)
{
    free(arena->ptr);
}

#endif // ARENA_H_

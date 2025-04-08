#ifndef CONVERSION_H_
#define CONVERSION_H_

#include <string.h>
#include <stdio.h>

// Custom includes
#include "clay.h"

#include "state.h"

#define CONVERSION_BUFFER_LENGTH 1024

char conversion_buffer[CONVERSION_BUFFER_LENGTH] = {0};

#define string_to_clay_string(str)                                         \
    (!str ? CLAY_STRING("0") : (Clay_String) { .length = (int32_t) strlen(str), .chars = str })

char *int_to_str(int num)
{
    memset(conversion_buffer, 0, CONVERSION_BUFFER_LENGTH);
    snprintf(conversion_buffer, CONVERSION_BUFFER_LENGTH, "%d", num);

    // Adding \0 inside the size
    size_t str_size = strlen(conversion_buffer) + 1;
    
    char *str = arena_calloc(&application_state.layout_arena, str_size);
    memcpy(str, conversion_buffer, str_size);

    return str;
}

char *float_to_str(float num)
{
    memset(conversion_buffer, 0, CONVERSION_BUFFER_LENGTH);
    snprintf(conversion_buffer, CONVERSION_BUFFER_LENGTH, "%.2f", num);

    // Adding \0 inside the size
    size_t str_size = strlen(conversion_buffer) + 1;
    
    char *str = arena_calloc(&application_state.layout_arena, str_size);
    memcpy(str, conversion_buffer, str_size);

    return str;
}

#endif // CONVERSION_H_

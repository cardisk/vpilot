#ifndef CONVERSION_H_
#define CONVERSION_H_

#include <string.h>
#include <stdio.h>

// Custom includes
#include "clay.h"

#define CONVERSION_BUFFER_LENGTH 1024

char conversion_buffer[CONVERSION_BUFFER_LENGTH] = {0};

#define buffer_to_clay_string()                                         \
    (!strlen(conversion_buffer) ? CLAY_STRING("0") : (Clay_String) { .length = (int32_t) strlen(conversion_buffer), .chars = conversion_buffer })

#define int_to_str(num)                                                 \
    memset(conversion_buffer, 0, CONVERSION_BUFFER_LENGTH);             \
    snprintf(conversion_buffer, CONVERSION_BUFFER_LENGTH, "%d", num)

#define float_to_str(num)                                               \
    memset(conversion_buffer, 0, CONVERSION_BUFFER_LENGTH);             \
    snprintf(conversion_buffer, CONVERSION_BUFFER_LENGTH, "%.2f", num)

#endif // CONVERSION_H_

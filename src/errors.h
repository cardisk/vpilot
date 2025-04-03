#ifndef ERRORS_H_
#define ERRORS_H_

#include <stdint.h>

struct Error_
{
    // Error group
	uint8_t group_id;
    // Error id inside the group
	uint8_t msg_id;
};

typedef struct Error_ Error;

struct Errors_
{
    Error *ptr;
    int length;
    int capacity;
};

typedef struct Errors_ Errors;

#endif // ERRORS_H_

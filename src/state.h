#ifndef STATE_H_
#define STATE_H_

// Custom includes
#ifdef CAN_AVAILABLE
#  include "can.h"
#endif

#define VP_UPDATE_SUCCESS 0
#define VP_UPDATE_SKIP 1
#define VP_UPDATE_FAIL -1

// Application state
struct VPilot_
{
#ifdef CAN_AVAILABLE
    int can_socket;
#endif
};

typedef struct VPilot_ VPilot;

// Globals
const VPilot application_state = {};

int vp_init()
{
#ifdef CAN_AVAILABLE
    int fd = can_init();

    // Just propagate the failure
    if (fd < 0) return -1;

    application_state.can_socket = fd;
#endif
    return 0;
}

int vp_update()
{
#ifdef CAN_AVAILABLE
    struct can_frame frame;
    int read_result = can_read(application_state.can_socket, &frame);

    switch (read_result)
    {
        case CAN_READ_SKIP:
            return VP_UPDATE_SKIP;

        case CAN_READ_FAIL:
            return VP_UPDATE_FAIL;
    }

    // TODO: Set the state accordingly
#endif

    return VP_UPDATE_SUCCESS;
}

#endif // STATE_H_

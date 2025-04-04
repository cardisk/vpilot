#ifndef STATE_H_
#define STATE_H_

#include <stdint.h>
#include <stdbool.h>

// Custom includes
#ifdef CAN_AVAILABLE
#  include "can.h"
#endif

#include "array.h"
#include "errors.h"

#define VP_UPDATE_SUCCESS 0
#define VP_UPDATE_SKIP 1
#define VP_UPDATE_FAIL -1

// Application state
struct VPilot_
{
    struct
    {
        uint16_t front_pressure;
        uint16_t rear_pressure;
        uint8_t  bias;
    } brake;

    struct
    {
        uint8_t info_message;
        Errors errors;
    } logs;

    struct
    {
        float voltage_12V;
        uint8_t soc;

        uint8_t bms_voltage;
        uint8_t bms_temperature;
    } battery;

    struct
    {
        uint16_t gps;

        uint16_t frontL;
        uint16_t frontR;

        uint16_t rearL;
        uint16_t rearR;
    } speed;

	uint8_t lapTimeForTesting;
	float oilPressure;
	uint16_t waterTemperature;
	uint16_t airTemperature;
	uint16_t engineRPM;
	uint8_t gear;
	float manifoldPressure;
	uint16_t turboPressure;
	float fuelPressure;
	int16_t tps;
	int16_t gas;

#ifdef CAN_AVAILABLE
    int can_socket;
#endif
};

typedef struct VPilot_ VPilot;

// Globals
VPilot application_state = {0};

int vp_init()
{
#ifdef CAN_AVAILABLE
    int fd = can_init("vcan0");

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

    switch (frame.can_id)
    {
        case 101:
            application_state.brake.front_pressure = (frame.data[0] << 8) | frame.data[1];
            application_state.brake.rear_pressure  = (frame.data[2] << 8) | frame.data[3];
            break;

        case 400:
            // TODO: Error logging
            return VP_UPDATE_FAIL;

        case 401:
            application_state.logs.info_message = frame.data[0];
            break;
            
        case 402:
            // Ignoring HARD RESET
            break;

        case 403:
            {
                Error e = { 
                    .group_id = frame.data[0], 
                    .msg_id = frame.data[1],
                };

                bool found = false;
                array_foreach(&application_state.logs.errors, Error, it)
                {
                    if (memcmp(&e, it, sizeof(Error)) == 0)
                    {
                        found = true;
                        break;
                    }
                }

                if (found) break;

                array_push(&application_state.logs.errors, e);
            }
            break;
    }
#endif

    return VP_UPDATE_SUCCESS;
}

#endif // STATE_H_

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
        Errors  errors;
    } logs;

    struct
    {
        float   voltage_12V;
        uint8_t soc;

        uint8_t bms_voltage;
        uint8_t bms_temperature;
    } battery;

    struct
    {
        uint16_t rpm;
        uint8_t  gear;
        int16_t  gas;
        int16_t  tps;
    } engine;

    struct
    {
        uint16_t gps;

        uint16_t frontL;
        uint16_t frontR;

        uint16_t rearL;
        uint16_t rearR;
    } speed;

    struct
    {
        float    oil;
        float    manifold;
        uint16_t turbo;
        float    fuel;
    } pressure;

    struct
    {
        uint16_t water;
        uint16_t air;
    } temperature;

	uint8_t lap_time_for_testing;

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

        case 700:
            application_state.speed.gps = (frame.data[1] << 8) | frame.data[0];
            break;

        case 701:
            application_state.lap_time_for_testing = data[0];
            break;

        case 702:
            application_state.battery.voltage_12V = (data[1] << 8) | data[0];
            break;

        case 703:
            application_state.brake.bias = data[0];
            break;

        case 800:
            application_state.speed.frontL = (data[1] << 8) | data[0];
            application_state.speed.frontR = (data[2] << 8) | data[3];
            application_state.speed.rearL  = (data[4] << 8) | data[5];
            application_state.speed.rearR  = (data[6] << 8) | data[7];
            break;

        case 801:
            application_state.pressure.oil  = ((float) ((data[1] << 8) | data[0])) / 100.0;
            application_state.pressure.fuel = ((float) ((data[3] << 8) | data[2])) / 100.0;
            break;

        case 802:
            application_state.temperature.water = ((data[1] << 8) | data[0]) / 10;
            application_state.temperature.air   = ((data[3] << 8) | data[2]) / 10;
            break;

        case 803:
            application_state.engine.tps        = ((data[1] << 8) | data[0]) / 10.0;
            application_state.pressure.turbo    =  (data[3] << 8) | data[2];
            application_state.pressure.manifold = ((float) ((data[5] << 8) | data[4])) / 1000.0;
            break;

        case 804:
            application_state.engine.gear = data[0];
            break;
        
        case 805:
            application_state.engine.rpm = (data[1] << 8) | data[0];
            application_state.engine.gas = (data[3] << 8) | data[2];
            break;
        
        case 900:
            application_state.battery.bms_voltage = data[0];
            break;
        
        case 901:
            application_state.battery.soc = data[0];
            break;
        
        case 902:
            application_state.battery.bms_temperature = data[0];
            break;

        default:
            ERR("Unhandled CAN frame id: %d", frame.can_id);
            return VP_UPDATE_FAIL;
    }
#endif

    return VP_UPDATE_SUCCESS;
}

#endif // STATE_H_

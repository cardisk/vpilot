#ifndef STATE_H_
#define STATE_H_

#include <stdint.h>
#include <stdbool.h>

// Custom includes
#ifdef CAN_AVAILABLE
#  include "can.h"
#endif

#include "array.h"
#include "arena.h"
#include "errors.h"

#define VP_UPDATE_SUCCESS 0
#define VP_UPDATE_SKIP 1
#define VP_UPDATE_FAIL -1

// Globals
const float ANT_COEFF  = 8.0 * 24.0 * 24.0 * 220.0;
const float REAR_COEFF = 4.0 * 27.0 * 27.0 * 200.0;

const char *gas_curve_table[] = {
    "LINEAR",
    "PARABOLIC",
};

const char *mission_table[] = {
    "MANUAL",
    "ACCELERATION",
    "SKIDPAD",
    "TRACKDRIVE",
    "EBS TEST",
    "AUT. INSPECTION",
    "AUTOCROSS",
};

#define MISSION_MODE_MANUAL     1
#define MISSION_MODE_AUTONOMOUS 2

enum Mission_
{
    NO_MISSION = 0,
    MANUAL,
    ACCELERATION,
    SKIDPAD,
    TRACKDRIVE,
    EBS_TEST,
    INSPECTION,
    AUTOCROSS,
};

typedef enum Mission_ Mission;

// Application state
struct VPilot_
{
    // Pilot state
    struct
    {
        uint16_t front_pressure;
        uint16_t rear_pressure;
        uint8_t  bias;
        int calculated_bias;
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

    bool is_forced_gear;
    Mission mission_selected;

    // VPilot state
#ifdef CAN_AVAILABLE
    int can_socket;
#endif

    Arena layout_arena;
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

    application_state.layout_arena = arena_init(1024 * 1024);
    return 0;
}

int vp_update()
{
    arena_clear(&application_state.layout_arena);

#ifdef CAN_AVAILABLE
    struct can_frame frame = {0};
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
            application_state.brake.front_pressure  = (frame.data[0] << 8) | frame.data[1];
            application_state.brake.rear_pressure   = (frame.data[2] << 8) | frame.data[3];
            application_state.brake.calculated_bias = (application_state.brake.front_pressure * 100.0f * ANT_COEFF) / ((application_state.brake.front_pressure * ANT_COEFF) + (application_state.brake.rear_pressure * REAR_COEFF));
            break;

        case 400:
            {
                Error e = { 
                    .group_id = frame.data[0], 
                    .msg_id = frame.data[1],
                };

                ERR("----------------------------------------------------------");
                ERR("!!>> %s", fatal_to_string(e));
                ERR("----------------------------------------------------------");
            }
            return VP_UPDATE_FAIL;

        case 401:
            application_state.logs.info_message = frame.data[0];
            break;
            
        case 402:
            vp_destroy();
            if (vp_init() < 0)
                return VP_UPDATE_FAIL;
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

                WARN("----------------------------------------------------------");
                array_foreach(&application_state.logs.errors, Error, it)
                {
                    WARN(">> %s", warning_to_string(*it));
                }
                WARN("----------------------------------------------------------");
            }
            break;

        case 700:
            application_state.speed.gps = (frame.data[1] << 8) | frame.data[0];
            break;

        case 701:
            application_state.lap_time_for_testing = frame.data[0];
            break;

        case 702:
            application_state.battery.voltage_12V = (frame.data[1] << 8) | frame.data[0];
            break;

        case 703:
            application_state.brake.bias = frame.data[0];
            break;

        case 800:
            application_state.speed.frontL = (frame.data[1] << 8) | frame.data[0];
            application_state.speed.frontR = (frame.data[2] << 8) | frame.data[3];
            application_state.speed.rearL  = (frame.data[4] << 8) | frame.data[5];
            application_state.speed.rearR  = (frame.data[6] << 8) | frame.data[7];
            break;

        case 801:
            application_state.pressure.oil  = ((float) ((frame.data[1] << 8) | frame.data[0])) / 100.0;
            application_state.pressure.fuel = ((float) ((frame.data[3] << 8) | frame.data[2])) / 100.0;
            break;

        case 802:
            application_state.temperature.water = ((frame.data[1] << 8) | frame.data[0]) / 10;
            application_state.temperature.air   = ((frame.data[3] << 8) | frame.data[2]) / 10;
            break;

        case 803:
            application_state.engine.tps        = ((frame.data[1] << 8) | frame.data[0]) / 10.0;
            application_state.pressure.turbo    =  (frame.data[3] << 8) | frame.data[2];
            application_state.pressure.manifold = ((float) ((frame.data[5] << 8) | frame.data[4])) / 1000.0;
            break;

        case 804:
            application_state.engine.gear = frame.data[0];
            break;
        
        case 805:
            application_state.engine.rpm = (frame.data[1] << 8) | frame.data[0];
            application_state.engine.gas = (frame.data[3] << 8) | frame.data[2];
            break;
        
        case 900:
            application_state.battery.bms_voltage = frame.data[0];
            break;
        
        case 901:
            application_state.battery.soc = frame.data[0];
            break;
        
        case 902:
            application_state.battery.bms_temperature = frame.data[0];
            break;

        default:
            ERR("Unhandled CAN frame id: %d", frame.can_id);
            return VP_UPDATE_FAIL;
    }
#endif

    return VP_UPDATE_SUCCESS;
}

void vp_destroy()
{
    array_free(application_state.logs.errors);
    arena_free(&application_state.layout_arena);

#ifdef CAN_AVAILABLE
    can_close(application_state.can_socket);
#endif
}

#endif // STATE_H_

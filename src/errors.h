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

char *fatal_to_string(Error e)
{
    switch (e.group_id)
    {
        case 13:
            return "APPS IMPLAUSIBILITY";

        case 14:
            switch (e.msg_id)
            {
                case 0:
                    return "IMPL. BRAKE PRES.";

                case 1:
                    return "NO PRES. AFTER QMS";

                case 2:
                    return "AIR PRES. LOW AFTER QMS";

                default:
                    return "UNKNOWN ASBCHECK MSG ID.";
            }
            break;

        case 15:
            switch (e.msg_id)
            {
                case 0:
                    return "CAN COMM. ERR";

                case 1:
                    return "NO HB FOR >200ms";

                case 2:
                    return "EBS AIR PRES. TOO LOW";

                case 3:
                    return "RES ERR.";

                default:
                    return "UNKNOWN ERRORHANDASTASK MSG ID.";
            }
            break;
        
        case 18:
            return "TPS IMPL. WITH APPS";

        case 20:
            return "ERROR, FAN TEMP>108°C, FAN FAILURE";

        default:
            return "UNKNOWN FATAL GROUP ID.";
    }
}

char *warning_to_string(Error e)
{
    switch (e.group_id)
    {
        case 10:
            return "MANUAL OR NO MISS. SEL.";
        
        case 11:
            return "ASMS OFF";

        case 12:
            return "NO MIS. SEL. AND TS ON";

        case 16:
            switch (e.msg_id)
            {
                case 0:
                    return "NO AIR TO CHANGE GEAR";

                default:
                    return "UNKNOWN GEARTASK MSG ID.";
            }
            break;

        case 17:
            return "REMOVE GEAR BEFORE STARTING IN AUT.";

        case 19:
            return "WARNING, FAN TEMP>100°C";

        case 21:
            switch (e.msg_id)
            {
                case 0:
                    return "WRONG MESSAGE -> CAN COMM. ERROR";
                
                case 1:
                    return "LOW FUEL PRESSURE";

                case 2:
                    return "LOW OIL PRESSURE";

                default:
                    return "UNKNOWN ERRORHANDTASK MSG ID.";
            }
            break;

        default:
            return "UNKNOWN WARN GROUP ID.";
    }
}

#endif // ERRORS_H_

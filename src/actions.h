#ifndef ACTIONS_H_
#define ACTIONS_H_

#include <stdio.h>
#include <assert.h>

// CLAY includes
#include "clay.h"

// Custom includes
#include "shared.h"

#ifdef CAN_AVAILABLE
#  include "can.h"
#endif

void clay_log_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Some DATA are passed to ClayLogAction function\n");
    
    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        LOG("CLICK: '%s'", element_id.stringId.chars);
    }
}

#ifdef CAN_AVAILABLE
void drive_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");

    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        // dlc = 1, id = 302, data[0] = 2
        can_write(application_state.can_socket, 302, 2);
    }
}

void hard_reset_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");

    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        // dlc = 1, id = 291, data[0] = 255
        can_write(application_state.can_socket, 291, 255);
    }
}

void neutral_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");

    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        // If Forced Gear is active there is no need to re-send it
        if (application_state.is_forced_gear) return;
        // Neutral is only permitted if in the first gear
        if (application_state.engine.gear != 1) return;

        application_state.is_forced_gear = true;

        // dlc = 1, id = 302, data[0] = 1
        can_write(application_state.can_socket, 302, 1);
    }
}

void launch_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");

    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        // dlc = 1, id = 302, data[0] = 3
        can_write(application_state.can_socket, 302, 3);
    }
}

void forced_gear_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");

    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        // If Forced Gear is active there is no need to re-send it
        if (application_state.is_forced_gear) return;

        // dlc = 1, id = 303, data[0] = 1
        can_write(application_state.can_socket, 303, 1);
    }
}

void tag_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");

    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        // dlc = 1, id = 302, data[0] = 4
        can_write(application_state.can_socket, 302, 4);
    }
}

void ok_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");
}

void gas_curve_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        switch (data)
        {
            case 0:
                // dlc = 1, id = 305, data[0] = 0
                can_write(application_state.can_socket, 305, 0);
                break;

            case 1:
                // dlc = 1, id = 305, data[0] = 1
                can_write(application_state.can_socket, 305, 1);
                break;

            default:
                assert(0 && "unreachable: gas_curve_action not handled");
                break;
        }
    }
}

void mission_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        Mission mission = (Mission) data;

        switch (mission)
        {
            case NO_MISSION:
                assert(0 && "unreachable: NO_MISSION should not appear here");

            case MANUAL:
                can_write(application_state.can_socket, 290, MISSION_MODE_MANUAL,     (int) (mission - 1));
                break;

            case ACCELERATION:
                can_write(application_state.can_socket, 290, MISSION_MODE_AUTONOMOUS, (int) (mission - 1));
                break;

            case SKIDPAD:
                can_write(application_state.can_socket, 290, MISSION_MODE_AUTONOMOUS, (int) (mission - 1));
                break;

            case TRACKDRIVE:
                can_write(application_state.can_socket, 290, MISSION_MODE_AUTONOMOUS, (int) (mission - 1));
                break;

            case EBS_TEST:
                can_write(application_state.can_socket, 290, MISSION_MODE_AUTONOMOUS, (int) (mission - 1));
                break;

            case INSPECTION:
                can_write(application_state.can_socket, 290, MISSION_MODE_AUTONOMOUS, (int) (mission - 1));
                break;

            case AUTOCROSS:
                can_write(application_state.can_socket, 290, MISSION_MODE_AUTONOMOUS, (int) (mission - 1));
                break;

            default:
                assert(0 && "unreachable: mission_action doesn't handle this mission");
        }

        application_state.mission_selected = mission;
    }
}

void gear_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data != 0 && "Gear shift should be UP (1) or DOWN (-1), not 0");

    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        if (data < 0)
        {
            // Downshift

            // dlc = 1, id = 301, data[0] = 2
            can_write(application_state.can_socket, 301, 2);
        }
        
        if (data > 0)
        {
            // Upshift

            // dlc = 1, id = 301, data[0] = 1
            can_write(application_state.can_socket, 301, 1);
        }
    }
}
#endif

#endif // ACTIONS_H_

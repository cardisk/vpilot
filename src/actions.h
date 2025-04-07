#ifndef ACTIONS_H_
#define ACTIONS_H_

#include <stdio.h>
#include <assert.h>

// CLAY includes
#include "clay.h"

// Custom includes
#include "shared.h"

void clay_log_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Some DATA are passed to ClayLogAction function\n");
    
    if (pointer_info.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        LOG("CLICK: '%s'\n", element_id.stringId.chars);
    }
}

#ifdef CAN_AVAILABLE
void drive_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");
}

void neutral_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");
}

void launch_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");
}

void forced_gear_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");
}

void tag_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");
}

void ok_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");
}

void gas_curve_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");
}

void mission_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data == CLAY_NULL && "Button actions are specific, no args needed");
}

void gear_action(Clay_ElementId element_id, Clay_PointerData pointer_info, intptr_t data)
{
    assert(data != 0 && "Gear shift should be UP (1) or DOWN (-1), not 0");

    if (data < 0)
    {
        // Gear down
    }
    
    if (data > 0)
    {
        // Gear up
    }

    assert(0 && "unreachable: gear_action");
}
#endif

#endif // ACTIONS_H_

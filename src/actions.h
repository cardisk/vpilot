#ifndef ACTIONS_H_
#define ACTIONS_H_

#include <stdio.h>
#include <assert.h>

// CLAY includes
#include "clay.h"

// Custom includes
#include "shared.h"

void ClayLogAction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    assert(userData == CLAY_NULL && "Some DATA are passed to ClayLogAction function\n");
    
    if (pointerInfo.state == CLAY_POINTER_DATA_PRESSED_THIS_FRAME)
    {
        LOG("CLICK: '%s'\n", elementId.stringId.chars);
    }
}

void DriveAction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    assert(userData == CLAY_NULL && "Button actions are specific, no args needed");
}

void NeutralAction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    assert(userData == CLAY_NULL && "Button actions are specific, no args needed");
}

void LaunchAction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    assert(userData == CLAY_NULL && "Button actions are specific, no args needed");
}

void ForcedGearAction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    assert(userData == CLAY_NULL && "Button actions are specific, no args needed");
}

void TagAction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    assert(userData == CLAY_NULL && "Button actions are specific, no args needed");
}

void OkAction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    assert(userData == CLAY_NULL && "Button actions are specific, no args needed");
}

void GasCurveAction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    assert(userData == CLAY_NULL && "Button actions are specific, no args needed");
}

void MissionAction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    assert(userData == CLAY_NULL && "Button actions are specific, no args needed");
}

void GearAction(Clay_ElementId elementId, Clay_PointerData pointerInfo, intptr_t userData)
{
    assert(userData == CLAY_NULL && "Button actions are specific, no args needed");
}

#endif // ACTIONS_H_

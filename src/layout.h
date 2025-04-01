#ifndef LAYOUT_H_
#define LAYOUT_H_

#include "clay.h"

// Background colors
const Clay_Color BTN_DRIVE = { 253, 218, 13, 255 };
const Clay_Color BTN_DRIVE_HOVER = { 253, 218, 13, 192 };

const Clay_Color BTN_NEUTRAL = { 0, 71, 171, 255 };
const Clay_Color BTN_NEUTRAL_HOVER = { 0, 71, 171, 192 };

const Clay_Color BTN_LAUNCH = { 210, 43, 43, 255 };
const Clay_Color BTN_LAUNCH_HOVER = { 210, 43, 43, 192 };

const Clay_Color BTN_TAG = { 210, 43, 43, 255 };
const Clay_Color BTN_TAG_HOVER = { 210, 43, 43, 192 };

const Clay_Color BTN_OK = { 64, 128, 64, 255 };
const Clay_Color BTN_OK_HOVER = { 64, 128, 64, 192 };

const Clay_Color SELECTOR = { 64, 64, 64, 255 };
const Clay_Color SELECTOR_HOVER = { 64, 64, 64, 192 };

const Clay_Color WHITE = { 255, 255, 255, 255 };
const Clay_Color BLACK = { 0, 0, 0, 255 };

Clay_RenderCommandArray vp_layout()
{
    // CLAY scope start
    Clay_BeginLayout();

    // Declarative layout
    CLAY({
        .layout = { 
            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
        },
    }) {
        CLAY({
            .layout = { 
                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_PERCENT(0.125) },
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
            },
        }) {
            CLAY({
                .layout = {
                    .sizing = { .width = CLAY_SIZING_PERCENT(0.5), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = Clay_Hovered() ? BTN_DRIVE_HOVER : BTN_DRIVE,
            }) {
                CLAY_TEXT(
                    CLAY_STRING("DRIVE"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = BLACK,
                    })
                );
            }
            CLAY({
                .layout = {
                    .sizing = { .width = CLAY_SIZING_PERCENT(0.5), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = Clay_Hovered() ? BTN_NEUTRAL_HOVER : BTN_NEUTRAL,
            }) {
                CLAY_TEXT(
                    CLAY_STRING("NEUTRAL"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = WHITE,
                    })
                );
            }
        }
        CLAY({
            .layout = { 
                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_PERCENT(0.125) },
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
            },
        }) {
            CLAY({
                .layout = {
                    .sizing = { .width = CLAY_SIZING_PERCENT(0.5), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                },
                .backgroundColor = Clay_Hovered() ? BTN_LAUNCH_HOVER : BTN_LAUNCH,
            }) {
                CLAY_TEXT(
                    CLAY_STRING("LAUNCH"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = BLACK,
                    })
                );
            }
            CLAY({
                .layout = {
                    .sizing = { .width = CLAY_SIZING_PERCENT(0.5), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = Clay_Hovered() ? BTN_TAG_HOVER : BTN_TAG,
            }) {
                CLAY_TEXT(
                    CLAY_STRING("TAG"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = BLACK,
                    })
                );
            }
        }
        CLAY({
            .layout = { 
                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
            },
            .backgroundColor = { 100, 64, 64, 255 },
        }) {
            // Insert here the gui part
        }
        CLAY({
            .layout = { 
                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_PERCENT(0.25) },
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
            },
        }) {
            CLAY({
                .layout = { 
                    .sizing = { .width = CLAY_SIZING_PERCENT(0.3), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                },
                .backgroundColor = { 128, 192, 128, 255 },
            }) {
                CLAY_TEXT(
                    CLAY_STRING("DOWN"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = BLACK,
                    })
                );
            }
            CLAY({
                .layout = { 
                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM,
                },
            }) {
                CLAY({
                    .layout = {
                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    },
                    .backgroundColor = Clay_Hovered() ? BTN_OK_HOVER : BTN_OK,
                }) {
                    CLAY_TEXT(
                        CLAY_STRING("OK"),
                        CLAY_TEXT_CONFIG({
                            .fontSize = 24,
                            .textColor = WHITE,
                        })
                    );
                }
                CLAY({
                    .layout = {
                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    },
                }) {
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                        .backgroundColor = Clay_Hovered() ? SELECTOR_HOVER : SELECTOR,
                    }) {
                        CLAY_TEXT(
                            CLAY_STRING("GAS CURVE"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 24,
                                .textColor = WHITE,
                            })
                        );
                    }
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                        .backgroundColor = Clay_Hovered() ? SELECTOR_HOVER : SELECTOR,
                    }) {
                        CLAY_TEXT(
                            CLAY_STRING("MISSION"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 24,
                                .textColor = WHITE,
                            })
                        );
                    }
                }
            }
            CLAY({
                .layout = { 
                    .sizing = { .width = CLAY_SIZING_PERCENT(0.3), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                },
                .backgroundColor = { 128, 192, 128, 255 },
            }) {
                CLAY_TEXT(
                    CLAY_STRING("UP"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = BLACK,
                    })
                );
            }
        }
    }

    // CLAY scope end, it returns the commands to render the layout
    return Clay_EndLayout();
}

#endif // LAYOUT_H_

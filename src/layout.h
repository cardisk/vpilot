#ifndef LAYOUT_H_
#define LAYOUT_H_

// CLAY includes
#include "clay.h"

// Custom includes
#include "shared.h"
#include "actions.h"
#include "state.h"
#include "conversion.h"

// Generic colors
const Clay_Color COLOR_WHITE = { 255, 255, 255, 255 };
const Clay_Color COLOR_BLACK = { 0, 0, 0, 255 };
const Clay_Color COLOR_SOFT_BLACK = { 18, 18, 18, 255 };
const Clay_Color COLOR_RED = { 255, 0, 0, 255 };
const Clay_Color COLOR_GREEN = { 0, 255, 0, 255 };
const Clay_Color COLOR_PURPLE = { 128, 0, 128, 255 };

// Components specific colors
const Clay_Color BTN_DRIVE = { 253, 218, 13, 255 };
const Clay_Color BTN_DRIVE_HOVER = { 253, 218, 13, 192 };

const Clay_Color BTN_HARD_RESET = { 112, 41, 99, 255 };
const Clay_Color BTN_HARD_RESET_HOVER = { 112, 41, 99, 192 };

const Clay_Color BTN_NEUTRAL = { 0, 71, 171, 255 };
const Clay_Color BTN_NEUTRAL_HOVER = { 0, 71, 171, 192 };

const Clay_Color BTN_LAUNCH = { 210, 43, 43, 255 };
const Clay_Color BTN_LAUNCH_HOVER = { 210, 43, 43, 192 };

const Clay_Color BTN_FORCED_GEAR = { 242, 140, 40, 255 };
const Clay_Color BTN_FORCED_GEAR_HOVER = { 242, 140, 40, 192 };

const Clay_Color BTN_TAG = { 210, 43, 43, 255 };
const Clay_Color BTN_TAG_HOVER = { 210, 43, 43, 192 };

const Clay_Color BTN_OK = { 64, 128, 64, 255 };
const Clay_Color BTN_OK_HOVER = { 64, 128, 64, 192 };

const Clay_Color SELECTOR = { 64, 64, 64, 255 };
const Clay_Color SELECTOR_HOVER = { 64, 64, 64, 192 };

const Clay_Color GEAR_SHIFT = { 128, 128, 128, 255 };
const Clay_Color GEAR_SHIFT_HOVER = { 128, 128, 128, 192 };

const Clay_Color FLOATING_COLOR = COLOR_PURPLE;
const Clay_Color FLOATING_COLOR_HOVER = { 100, 0, 100, 255 };

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
                .id = CLAY_ID("DriveButton"),
                .layout = {
                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = Clay_Hovered() ? BTN_DRIVE_HOVER : BTN_DRIVE,
            }) {
#ifdef CAN_AVAILABLE
                Clay_OnHover(&drive_action, CLAY_NULL);
#else
                Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif
                CLAY_TEXT(
                    CLAY_STRING("DRIVE"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = COLOR_BLACK,
                    })
                );
            }
            CLAY({
                .id = CLAY_ID("HardResetButton"),
                .layout = {
                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = Clay_Hovered() ? BTN_HARD_RESET_HOVER : BTN_HARD_RESET,
            }) {
#ifdef CAN_AVAILABLE
                Clay_OnHover(&hard_reset_action, CLAY_NULL);
#else
                Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif
                CLAY_TEXT(
                    CLAY_STRING("HARD RESET"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = COLOR_WHITE,
                    })
                );
            }
            CLAY({
                .id = CLAY_ID("NeutralButton"),
                .layout = {
                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = Clay_Hovered() ? BTN_NEUTRAL_HOVER : BTN_NEUTRAL,
            }) {
#ifdef CAN_AVAILABLE
                Clay_OnHover(&neutral_action, CLAY_NULL);
#else
                Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif
                CLAY_TEXT(
                    CLAY_STRING("NEUTRAL"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = COLOR_WHITE,
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
                .id = CLAY_ID("LaunchButton"),
                .layout = {
                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                },
                .backgroundColor = Clay_Hovered() ? BTN_LAUNCH_HOVER : BTN_LAUNCH,
            }) {
#ifdef CAN_AVAILABLE
                Clay_OnHover(&launch_action, CLAY_NULL);
#else
                Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif
                CLAY_TEXT(
                    CLAY_STRING("LAUNCH"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = COLOR_BLACK,
                    })
                );
            }
            CLAY({
                .id = CLAY_ID("ForcedGearButton"),
                .layout = {
                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                },
                .backgroundColor = Clay_Hovered() ? BTN_FORCED_GEAR_HOVER : BTN_FORCED_GEAR,
            }) {
#ifdef CAN_AVAILABLE
                Clay_OnHover(&forced_gear_action, CLAY_NULL);
#else
                Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif
                CLAY_TEXT(
                    CLAY_STRING("FORCED GEAR"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = COLOR_BLACK,
                    })
                );
            }
            CLAY({
                .id = CLAY_ID("TagButton"),
                .layout = {
                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER }
                },
                .backgroundColor = Clay_Hovered() ? BTN_TAG_HOVER : BTN_TAG,
            }) {
#ifdef CAN_AVAILABLE
                Clay_OnHover(&tag_action, CLAY_NULL);
#else
                Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif
                CLAY_TEXT(
                    CLAY_STRING("TAG"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = COLOR_BLACK,
                    })
                );
            }
        }
        CLAY({
            .id = CLAY_ID("GUI"),
            .layout = { 
                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
            },
        }) {
            switch (application_state.mission_selected)
            {
                case  NO_MISSION:
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                    }) {
                        CLAY_TEXT(
                            CLAY_STRING("PLEASE SELECT A MISSION"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 36,
                                .textColor = COLOR_WHITE,
                            })
                        );
                    }
                    break;

                case MANUAL:
                    // Top row
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .layoutDirection = CLAY_LEFT_TO_RIGHT,
                        },
                    }) {
                        CLAY({
                            .layout = { 
                                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                            },
                        }) {
                            CLAY({
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_PERCENT(0.33) },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                },
                                .border = {
                                    .color = COLOR_WHITE,
                                    .width = CLAY_BORDER_ALL(2),
                                },
                            }) {
                                CLAY_TEXT(
                                    CLAY_STRING("ENGINE RPM"),
                                    CLAY_TEXT_CONFIG({
                                        .fontSize = 18,
                                        .textColor = COLOR_RED,
                                    })
                                );
                            }
                            CLAY({
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                },
                                .border = {
                                    .color = COLOR_WHITE,
                                    .width = CLAY_BORDER_ALL(2),
                                },
                            }) {
                                char *str = int_to_str(application_state.engine.rpm);

                                CLAY_TEXT(
                                    string_to_clay_string(str),
                                    CLAY_TEXT_CONFIG({
                                        .fontSize = 36,
                                        .textColor = COLOR_WHITE,
                                    })
                                );
                            }
                        }
                        CLAY({
                            .layout = { 
                                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                                .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                            },
                        }) {
                            CLAY({
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                },
                                .border = {
                                    .color = COLOR_WHITE,
                                    .width = CLAY_BORDER_ALL(2),
                                },
                            }) {
                                char *str = int_to_str(application_state.speed.gps);

                                CLAY_TEXT(
                                    string_to_clay_string(str),
                                    CLAY_TEXT_CONFIG({
                                        .fontSize = 36,
                                        .textColor = COLOR_WHITE,
                                    })
                                );
                            }
                        }
                        CLAY({
                            .layout = { 
                                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                            },
                        }) {
                            CLAY({
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_PERCENT(0.33) },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                },
                                .border = {
                                    .color = COLOR_WHITE,
                                    .width = CLAY_BORDER_ALL(2),
                                },
                            }) {
                                CLAY_TEXT(
                                    CLAY_STRING("WTS"),
                                    CLAY_TEXT_CONFIG({
                                        .fontSize = 18,
                                        .textColor = COLOR_RED,
                                    })
                                );
                            }
                            CLAY({
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                },
                                .border = {
                                    .color = COLOR_WHITE,
                                    .width = CLAY_BORDER_ALL(2),
                                },
                            }) {
                                char *str = int_to_str(application_state.temperature.water);

                                CLAY_TEXT(
                                    string_to_clay_string(str),
                                    CLAY_TEXT_CONFIG({
                                        .fontSize = 36,
                                        .textColor = COLOR_WHITE,
                                    })
                                );
                            }
                        }
                    }
                    // Center row
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .layoutDirection = CLAY_LEFT_TO_RIGHT,
                        },
                        .border = {
                            .color = COLOR_WHITE,
                            .width = CLAY_BORDER_ALL(2),
                        },
                    }) {
                        CLAY({
                            .layout = { 
                                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                            },
                        }) {
                            CLAY({
                                .layout = { 
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                                },
                            }) {
                                CLAY({
                                    .layout = {
                                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    },
                                    .border = {
                                        .color = COLOR_WHITE,
                                        .width = { 2, 0, 2, 2, 2 },
                                    },
                                }) {
                                    CLAY_TEXT(
                                        CLAY_STRING("OPS"),
                                        CLAY_TEXT_CONFIG({
                                            .fontSize = 18,
                                            .textColor = COLOR_WHITE,
                                        })
                                    );
                                }
                                CLAY({
                                    .layout = {
                                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    },
                                    .border = {
                                        .color = COLOR_WHITE,
                                        .width = { 0, 2, 2, 2, 2 },
                                    },
                                }) {
                                    char *str = float_to_str(application_state.pressure.oil);

                                    CLAY_TEXT(
                                        string_to_clay_string(str),
                                        CLAY_TEXT_CONFIG({
                                            .fontSize = 18,
                                            .textColor = COLOR_WHITE,
                                        })
                                    );
                                }
                            }
                            CLAY({
                                .layout = { 
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                                },
                            }) {
                                CLAY({
                                    .layout = {
                                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    },
                                    .border = {
                                        .color = COLOR_WHITE,
                                        .width = { 2, 0, 2, 2, 2 },
                                    },
                                }) {
                                    CLAY_TEXT(
                                        CLAY_STRING("MAPS"),
                                        CLAY_TEXT_CONFIG({
                                            .fontSize = 18,
                                            .textColor = COLOR_WHITE,
                                        })
                                    );
                                }
                                CLAY({
                                    .layout = {
                                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    },
                                    .border = {
                                        .color = COLOR_WHITE,
                                        .width = { 0, 2, 2, 2, 2 },
                                    },
                                }) {
                                    char *str = float_to_str(application_state.pressure.manifold);

                                    CLAY_TEXT(
                                        string_to_clay_string(str),
                                        CLAY_TEXT_CONFIG({
                                            .fontSize = 18,
                                            .textColor = COLOR_WHITE,
                                        })
                                    );
                                }
                            }
                            CLAY({
                                .layout = { 
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                                },
                            }) {
                                CLAY({
                                    .layout = {
                                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    },
                                    .border = {
                                        .color = COLOR_WHITE,
                                        .width = { 2, 0, 2, 2, 2 },
                                    },
                                }) {
                                    CLAY_TEXT(
                                        CLAY_STRING("FPS"),
                                        CLAY_TEXT_CONFIG({
                                            .fontSize = 18,
                                            .textColor = COLOR_WHITE,
                                        })
                                    );
                                }
                                CLAY({
                                    .layout = {
                                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    },
                                    .border = {
                                        .color = COLOR_WHITE,
                                        .width = { 0, 2, 2, 2, 2 },
                                    },
                                }) {
                                    char *str = float_to_str(application_state.pressure.fuel);

                                    CLAY_TEXT(
                                        string_to_clay_string(str),
                                        CLAY_TEXT_CONFIG({
                                            .fontSize = 18,
                                            .textColor = COLOR_WHITE,
                                        })
                                    );
                                }
                            }
                            CLAY({
                                .layout = { 
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                                },
                            }) {
                                CLAY({
                                    .layout = {
                                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    },
                                    .border = {
                                        .color = COLOR_WHITE,
                                        .width = { 2, 0, 2, 2, 2 },
                                    },
                                }) {
                                    CLAY_TEXT(
                                        CLAY_STRING("12V"),
                                        CLAY_TEXT_CONFIG({
                                            .fontSize = 18,
                                            .textColor = COLOR_WHITE,
                                        })
                                    );
                                }
                                CLAY({
                                    .layout = {
                                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    },
                                    .border = {
                                        .color = COLOR_WHITE,
                                        .width = { 0, 2, 2, 2, 2 },
                                    },
                                }) {
                                    char *str = float_to_str(application_state.battery.voltage_12V);

                                    CLAY_TEXT(
                                        string_to_clay_string(str),
                                        CLAY_TEXT_CONFIG({
                                            .fontSize = 18,
                                            .textColor = COLOR_WHITE,
                                        })
                                    );
                                }
                            }
                        }
                        CLAY({
                            .layout = { 
                                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                            },
                        }) {
                            CLAY({
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_PERCENT(0.33) },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                },
                                .backgroundColor = COLOR_WHITE,
                                .border = {
                                    .color = COLOR_WHITE,
                                    .width = CLAY_BORDER_ALL(2),
                                },
                            }) {
                                CLAY_TEXT(
                                    CLAY_STRING("GEAR"),
                                    CLAY_TEXT_CONFIG({
                                        .fontSize = 18,
                                        .textColor = COLOR_BLACK,
                                    })
                                );
                            }
                            CLAY({
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                },
                                .border = {
                                    .color = COLOR_WHITE,
                                    .width = CLAY_BORDER_ALL(2),
                                },
                            }) {
                                char *str = int_to_str(application_state.engine.gear);

                                Clay_String text;
                                if (application_state.engine.gear == 0)
                                    text = CLAY_STRING("N");
                                else
                                    text = string_to_clay_string(str);

                                CLAY_TEXT(
                                    text,
                                    CLAY_TEXT_CONFIG({
                                        .fontSize = 48,
                                        .textColor = COLOR_GREEN,
                                    })
                                );
                            }
                        }
                        CLAY({
                            .layout = { 
                                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                            },
                        }) {
                            CLAY({
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_PERCENT(0.33) },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                },
                                .border = {
                                    .color = COLOR_WHITE,
                                    .width = CLAY_BORDER_ALL(2),
                                },
                            }) {
                                CLAY_TEXT(
                                    CLAY_STRING("BRAKE BIAS (%)"),
                                    CLAY_TEXT_CONFIG({
                                        .fontSize = 18,
                                        .textColor = COLOR_RED,
                                    })
                                );
                            }
                            CLAY({
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                                },
                                .border = {
                                    .color = COLOR_WHITE,
                                    .width = CLAY_BORDER_ALL(2),
                                },
                            }) {
                                char *str = int_to_str(application_state.brake.calculated_bias);

                                CLAY_TEXT(
                                    string_to_clay_string(str),
                                    CLAY_TEXT_CONFIG({
                                        .fontSize = 36,
                                        .textColor = COLOR_WHITE,
                                    })
                                );
                            }
                        }
                    }
                    // Bottom row
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .layoutDirection = CLAY_LEFT_TO_RIGHT,
                        },
                    }) {
                        CLAY({
                            .layout = { 
                                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                            },
                            .border = {
                                .color = COLOR_WHITE,
                                .width = CLAY_BORDER_ALL(2),
                            },
                        }) {
                            CLAY({
                                .id = CLAY_ID("GasCurve"),
                                .layout = { 
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                },
                            }) {
                            }
                            CLAY({
                                .id = CLAY_ID("InfoMessages"),
                                .layout = { 
                                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                },
                            }) {
                            }
                        }
                        CLAY({
                            .layout = { 
                                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                            },
                            .border = {
                                .color = COLOR_WHITE,
                                .width = CLAY_BORDER_ALL(2),
                            },
                        }) {
                            CLAY_TEXT(
                                CLAY_STRING("ERROR LOGS INSIDE TERMINAL"),
                                CLAY_TEXT_CONFIG({
                                    .fontSize = 18,
                                    .textColor = COLOR_RED,
                                })
                            );
                        }
                    }
                    break;

                case ACCELERATION:
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                    }) {
                        CLAY_TEXT(
                            CLAY_STRING("ACCELERATION"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 36,
                                .textColor = COLOR_WHITE,
                            })
                        );
                    }
                    break;

                case SKIDPAD:
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                    }) {
                        CLAY_TEXT(
                            CLAY_STRING("SKIDPAD"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 36,
                                .textColor = COLOR_WHITE,
                            })
                        );
                    }
                    break;

                case TRACKDRIVE:
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                    }) {
                        CLAY_TEXT(
                            CLAY_STRING("TRACKDRIVE"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 36,
                                .textColor = COLOR_WHITE,
                            })
                        );
                    }
                    break;

                case EBS_TEST:
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                    }) {
                        CLAY_TEXT(
                            CLAY_STRING("EBS TEST"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 36,
                                .textColor = COLOR_WHITE,
                            })
                        );
                    }
                    break;

                case INSPECTION:
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                    }) {
                        CLAY_TEXT(
                            CLAY_STRING("AUT. INSPECTION"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 36,
                                .textColor = COLOR_WHITE,
                            })
                        );
                    }
                    break;

                case AUTOCROSS:
                    CLAY({
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                    }) {
                        CLAY_TEXT(
                            CLAY_STRING("AUTOCROSS"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 36,
                                .textColor = COLOR_WHITE,
                            })
                        );
                    }
                    break;

                default:
                    assert(0 && "unreachable: mission requested is not available");
                    break;
            }
        }
        CLAY({
            .layout = { 
                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_PERCENT(0.25) },
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
            },
        }) {
            CLAY({
                .id = CLAY_ID("GearDownButton"),
                .layout = { 
                    .sizing = { .width = CLAY_SIZING_PERCENT(0.3), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                },
                .backgroundColor = Clay_Hovered() ?  GEAR_SHIFT_HOVER : GEAR_SHIFT,
            }) {
#ifdef CAN_AVAILABLE
                Clay_OnHover(&gear_action, (intptr_t) -1);
#else
                Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif
                CLAY_TEXT(
                    CLAY_STRING("DOWN"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = COLOR_BLACK,
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
                    },
                }) {
                    CLAY({
                        .id = CLAY_ID("GasCurveSelector"),
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                        .backgroundColor = Clay_Hovered() ? SELECTOR_HOVER : SELECTOR,
                    }) {
                        Clay_ElementId gas_curve_selector_id = Clay_GetElementId(CLAY_STRING("GasCurveSelector"));

                        bool is_floating_visible = 
                            Clay_PointerOver(gas_curve_selector_id)
                            || 
                            Clay_PointerOver(Clay_GetElementId(CLAY_STRING("FloatingCurveSelector")));

                        if (is_floating_visible)
                        {
                            Clay_ElementData gas_curve_selector_data = Clay_GetElementData(gas_curve_selector_id);

                            CLAY({
                                .id = CLAY_ID("FloatingCurveSelector"),
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_FIXED(gas_curve_selector_data.boundingBox.width), .height = CLAY_SIZING_GROW() },
                                    .layoutDirection = CLAY_TOP_TO_BOTTOM,
                                },
                                .floating = {
                                    .parentId = CLAY_ID("GUI").id,
                                    .attachTo = CLAY_ATTACH_TO_ELEMENT_WITH_ID,
                                    .attachPoints = { CLAY_ATTACH_POINT_RIGHT_BOTTOM, CLAY_ATTACH_POINT_CENTER_BOTTOM },
                                    .zIndex = 1,
                                },
                            }) {
                                for (int i = 0; i < ARRAY_LEN(gas_curve_table); i++)
                                {
                                    char *str = arena_copy_string(&application_state.layout_arena, gas_curve_table[i]);
                                    
                                    CLAY({
                                        .layout = {
                                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                        },
                                        .border = {
                                            .color = Clay_Hovered() ? FLOATING_COLOR_HOVER : FLOATING_COLOR,
                                            .width = CLAY_BORDER_ALL(2),
                                        },
                                        .backgroundColor = Clay_Hovered() ? FLOATING_COLOR_HOVER : FLOATING_COLOR,
                                    }) {
#ifdef CAN_AVAILABLE
                                        Clay_OnHover(&gas_curve_action, (intptr_t) i);
#else
                                        Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif

                                        CLAY_TEXT(
                                            string_to_clay_string(str),
                                            CLAY_TEXT_CONFIG({
                                                .fontSize = 18,
                                                .textColor = COLOR_WHITE,
                                            })
                                        );
                                    }
                                }
                            }
                        }

                        CLAY_TEXT(
                            CLAY_STRING("GAS CURVE"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 24,
                                .textColor = COLOR_WHITE,
                            })
                        );
                    }
                    CLAY({
                        .id = CLAY_ID("MissionSelector"),
                        .layout = { 
                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        },
                        .backgroundColor = Clay_Hovered() ? SELECTOR_HOVER : SELECTOR,
                    }) {
                        Clay_ElementId mission_selector_id = Clay_GetElementId(CLAY_STRING("MissionSelector"));

                        bool is_floating_visible = 
                            Clay_PointerOver(mission_selector_id)
                            || 
                            Clay_PointerOver(Clay_GetElementId(CLAY_STRING("FloatingMissionSelector")));

                        if (is_floating_visible)
                        {
                            Clay_ElementData mission_selector_data = Clay_GetElementData(mission_selector_id);

                            CLAY({
                                .id = CLAY_ID("FloatingMissionSelector"),
                                .layout = {
                                    .sizing = { .width = CLAY_SIZING_FIXED(mission_selector_data.boundingBox.width), .height = CLAY_SIZING_GROW() },
                                    .layoutDirection = CLAY_TOP_TO_BOTTOM,
                                },
                                .floating = {
                                    .parentId = CLAY_ID("GUI").id,
                                    .attachTo = CLAY_ATTACH_TO_ELEMENT_WITH_ID,
                                    .attachPoints = { CLAY_ATTACH_POINT_LEFT_BOTTOM, CLAY_ATTACH_POINT_CENTER_BOTTOM },
                                    .zIndex = 1,
                                },
                            }) {
                                for (int i = 0; i < ARRAY_LEN(mission_table); i++)
                                {
                                    char *str = arena_copy_string(&application_state.layout_arena, mission_table[i]);
                                    
                                    CLAY({
                                        .layout = {
                                            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                        },
                                        .border = {
                                            .color = Clay_Hovered() ? FLOATING_COLOR_HOVER : FLOATING_COLOR,
                                            .width = CLAY_BORDER_ALL(2),
                                        },
                                        .backgroundColor = Clay_Hovered() ? FLOATING_COLOR_HOVER : FLOATING_COLOR,
                                    }) {
#ifdef CAN_AVAILABLE
                                        // Mission enumeration is offset by 1
                                        Clay_OnHover(&mission_action, (intptr_t) i + 1);
#else
                                        Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif

                                        CLAY_TEXT(
                                            string_to_clay_string(str),
                                            CLAY_TEXT_CONFIG({
                                                .fontSize = 18,
                                                .textColor = COLOR_WHITE,
                                            })
                                        );
                                    }
                                }
                            }
                        }

                        CLAY_TEXT(
                            CLAY_STRING("MISSION"),
                            CLAY_TEXT_CONFIG({
                                .fontSize = 24,
                                .textColor = COLOR_WHITE,
                            })
                        );
                    }
                }
                CLAY({
                    .id = CLAY_ID("OkButton"),
                    .layout = {
                        .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    },
                    .backgroundColor = Clay_Hovered() ? BTN_OK_HOVER : BTN_OK,
                }) {
#ifdef CAN_AVAILABLE
                    Clay_OnHover(&ok_action, CLAY_NULL);
#else
                    Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif
                    CLAY_TEXT(
                        CLAY_STRING("OK"),
                        CLAY_TEXT_CONFIG({
                            .fontSize = 24,
                            .textColor = COLOR_WHITE,
                        })
                    );
                }
            }
            CLAY({
                .id = CLAY_ID("GearUpButton"),
                .layout = { 
                    .sizing = { .width = CLAY_SIZING_PERCENT(0.3), .height = CLAY_SIZING_GROW() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                },
                .backgroundColor = Clay_Hovered() ? GEAR_SHIFT_HOVER : GEAR_SHIFT,
            }) {
#ifdef CAN_AVAILABLE
                Clay_OnHover(&gear_action, (intptr_t) 1);
#else
                Clay_OnHover(&clay_log_action, CLAY_NULL);
#endif
                CLAY_TEXT(
                    CLAY_STRING("UP"),
                    CLAY_TEXT_CONFIG({
                        .fontSize = 24,
                        .textColor = COLOR_BLACK,
                    })
                );
            }
        }
    }

    // CLAY scope end, it returns the commands to render the layout
    return Clay_EndLayout();
}

#endif // LAYOUT_H_

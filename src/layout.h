#ifndef LAYOUT_H_
#define LAYOUT_H_

#include "clay.h"

Clay_RenderCommandArray vp_layout(int w, int h)
{
    // Like Raylib, CLAY scope start
    Clay_BeginLayout();

    // Declarative layout
    CLAY({
        .layout = { 
            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
        },
        .backgroundColor = { 18, 18, 18, 255 },
    }) {
        CLAY({
            .layout = { 
                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIXED(h / 8) },
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
            },
            .backgroundColor = { 128, 64, 64, 255 },
        }) {
            // Insert here the two upper buttons
        }
        CLAY({
            .layout = { 
                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIXED(h / 8) },
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
            },
            .backgroundColor = { 128, 32, 32, 255 },
        }) {
            // Insert here the two central buttons
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
                .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIXED(h / 4) },
                .layoutDirection = CLAY_LEFT_TO_RIGHT,
            },
        }) {
            CLAY({
                .layout = { 
                    .sizing = { .width = CLAY_SIZING_FIXED(w / 4), .height = CLAY_SIZING_GROW() },
                },
                .backgroundColor = { 200, 64, 64, 255 },
            }) {
                // Insert here downshift
            }
            CLAY({
                .layout = { 
                    .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                },
                .backgroundColor = { 150, 255, 64, 255 },
            }) {
                // OK button on top and two selector menu on bottom
            }
            CLAY({
                .layout = { 
                    .sizing = { .width = CLAY_SIZING_FIXED(w / 4), .height = CLAY_SIZING_GROW() },
                },
                .backgroundColor = { 200, 64, 64, 255 },
            }) {
                // Insert here upshift
            }
        }
        /* CLAY({ */
        /*     .layout = { */ 
        /*         .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIXED(h / 8) }, */
        /*         .layoutDirection = CLAY_LEFT_TO_RIGHT, */
        /*     }, */
        /*     .backgroundColor = { 128, 64, 64, 255 }, */
        /* }) { */
        /*     // Insert here the ok button */
        /* } */
        /* CLAY({ */
        /*     .layout = { */ 
        /*         .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIXED(h / 8) }, */
        /*         .layoutDirection = CLAY_LEFT_TO_RIGHT, */
        /*     }, */
        /*     .backgroundColor = { 128, 32, 32, 255 }, */
        /* }) { */
        /*     // Insert here the upshift and downshift */
        /* } */
    }

    // CLAY scope end, it returns the commands to render the layout
    return Clay_EndLayout();
}

#endif // LAYOUT_H_

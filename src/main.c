#include "renderers/raylib/raylib.h"
#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "renderers/raylib/clay_renderer_raylib.c"

#include <stdio.h>

Clay_RenderCommandArray vp_layout()
{
    // Like Raylib, CLAY scope start
    Clay_BeginLayout();

    CLAY({ 
        .layout = { .sizing = { .width = GetScreenWidth(), .height = GetScreenHeight() } },
        .backgroundColor = { 18, 18, 18, 255 },
    }) {}

    // CLAY scope end, it returns the commands to render the layout
    return Clay_EndLayout();
}


void HandleClayErrors(Clay_ErrorData errorData)
{
    // Just logging, ignoring the error
    printf("%s\n", errorData.errorText.chars);
}

int main(void)
{
    // Init CLAY context
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
    Clay_Initialize(clayMemory, (Clay_Dimensions) { (float) GetScreenWidth(), (float) GetScreenHeight() }, (Clay_ErrorHandler) { HandleClayErrors, 0 });

    // Init Raylib renderer
    Clay_Raylib_Initialize(800, 600, "VPILOT", FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);

    // Font stuff
    Font fonts[2];
    fonts[0] = LoadFontEx("../resources/Roboto-Regular.ttf", 48, 0, 400);
	SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);
    fonts[1] = LoadFontEx("../resources/Roboto-Regular.ttf", 32, 0, 400);
    SetTextureFilter(fonts[1].texture, TEXTURE_FILTER_BILINEAR);
    Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

    // Game Loop
    while (!WindowShouldClose())
    {
        // Raylib drawing scope start
        BeginDrawing();
        ClearBackground(BLACK);

        // CLAY layout
        Clay_RenderCommandArray content = vp_layout();

        // CLAY rendering
        Clay_Raylib_Render(content, fonts);

        // Raylib drawing scope end
        EndDrawing();
    }

    // Shutting down the window
    Clay_Raylib_Close();

    return 0;
}

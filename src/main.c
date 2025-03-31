#include <stdio.h>

// CLAY includes

// No need to include nor define this in other files
#define CLAY_IMPLEMENTATION
#include "clay.h"

// CLAY renderers
#ifdef RENDERER_RAYLIB
#  include "renderers/raylib/raylib.h"
#  include "renderers/raylib/clay_renderer_raylib.c"
#endif

// Custom includes
#include "layout.h"

// CLAY error handler
void HandleClayErrors(Clay_ErrorData errorData)
{
    // Just logging, ignoring the error
    printf("%s\n", errorData.errorText.chars);
}

#ifdef RENDERER_RAYLIB
int raylib_main(void)
{
    // Init CLAY context
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
    Clay_Initialize(clayMemory, (Clay_Dimensions) { (float) GetScreenWidth(), (float) GetScreenHeight() }, (Clay_ErrorHandler) { HandleClayErrors, 0 });

    // Init Raylib renderer
    Clay_Raylib_Initialize(800, 600, "vpilot", FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_MSAA_4X_HINT);

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
        Clay_RenderCommandArray content = vp_layout(GetScreenWidth(), GetScreenHeight());

        // CLAY rendering
        Clay_Raylib_Render(content, fonts);

        // Raylib drawing scope end
        EndDrawing();
    }

    // Shutting down the window
    Clay_Raylib_Close();

    return 0;
}
#endif

int main(void)
{
#ifdef RENDERER_RAYLIB
    return raylib_main();
#endif

#if 0
#ifdef RENDERER_SDL2
    return sdl2_main();
#endif

#ifdef RENDERER_SDL3
    return sdl3_main();
#endif
#endif
}

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

#ifdef RENDERER_SDL2
#  include "renderers/SDL2/clay_renderer_SDL2.c"
#endif

// Custom includes
#include "shared.h"
#include "state.h"
#include "layout.h"

// CLAY error handler
void clay_handle_errors(Clay_ErrorData errorData)
{
    // Just logging, ignoring the error
    ERR("%s\n", errorData.errorText.chars);
}

#ifdef RENDERER_RAYLIB
int raylib_main(void)
{
    // Init CLAY context
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));
    Clay_Initialize(clayMemory, (Clay_Dimensions) { (float) GetScreenWidth(), (float) GetScreenHeight() }, (Clay_ErrorHandler) { clay_handle_errors, 0 });

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
    bool stopping = false;

    while (!WindowShouldClose() && !stopping)
    {
        switch (vp_update())
        {
            case VP_UPDATE_FAIL:
                // Some error occured, stopping...
                stopping = true;
                continue;

            case VP_UPDATE_SKIP:
                // Nothing to read...
            case VP_UPDATE_SUCCESS:
                // Ok to render
                break;
        }

        // Raylib drawing scope start
        BeginDrawing();
        ClearBackground(BLACK);

        // CLAY layout
        Clay_SetLayoutDimensions((Clay_Dimensions) { (float) GetScreenWidth(), (float) GetScreenHeight() });

        bool isMouseDown = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
        Clay_SetPointerState((Clay_Vector2) { GetMouseX(), GetMouseY() }, isMouseDown);

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
#endif

#ifdef RENDERER_SDL2
int sdl2_main(void)
{
    // Init SDL2 context
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        ERR("Could not init SDL2: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0)
    {
        ERR("Could not init TTF: %s\n", TTF_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) < 0)
    {
        ERR("Could not init IMG: %s\n", IMG_GetError());
        return 1;
    }

    // Antialisaing stuff
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    // SDL2 window
	SDL_Window  *window  = NULL;

    window = SDL_CreateWindow(
            "vpilot", 
            SDL_WINDOWPOS_UNDEFINED, 
            SDL_WINDOWPOS_UNDEFINED, 
            800, 600, 
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!window)
    {
        ERR("Could not create SDL2 window: %s\n", SDL_GetError());
        return 1;
    }

    // SDL2 renderer
    SDL_Renderer *renderer = NULL;

#ifdef VSYNC
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
#else
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#endif

    if (!renderer)
    {
        ERR("Could not create SDL2 renderer: %s\n", SDL_GetError());
        return 1;
    }

    // Alpha blending
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    // Init CLAY context
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

    int width  = 0; 
    int height = 0;
    SDL_GetWindowSize(window, &width, &height);
    Clay_Initialize(clayMemory, (Clay_Dimensions) { (float) width, (float) height }, (Clay_ErrorHandler) { clay_handle_errors, 0 });

    // Font stuff
    TTF_Font *font = TTF_OpenFont("../resources/Roboto-Regular.ttf", 16);

    if (!font) {
        ERR("Could not load font: %s\n", TTF_GetError());
        return 1;
    }

    SDL2_Font fonts[1] = {};

    fonts[0] = (SDL2_Font) {
        .fontId = 0,
        .font = font,
    };

    Clay_SetMeasureTextFunction(SDL2_MeasureText, &fonts);

    // Game loop
    while (true)
    {
        switch (vp_update())
        {
            case VP_UPDATE_FAIL:
                // Some error occured, stopping...
                {
                    SDL_Event event;
                    event.type = SDL_QUIT;
                    SDL_PushEvent(&event);
                }
                break;

            case VP_UPDATE_SKIP:
                // Nothing to read...
            case VP_UPDATE_SUCCESS:
                // Ok to render
                break;
        }

        SDL_GetWindowSize(window, &width, &height);

        int mouseX = 0;
        int mouseY = 0;
        bool isMouseDown = false;
        SDL_GetMouseState(&mouseX, &mouseY);

        // SDL2 events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    goto QUIT;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                        isMouseDown = true;
            }
        }

        // CLAY layout
        Clay_SetLayoutDimensions((Clay_Dimensions) { (float) width, (float) height });
        Clay_SetPointerState((Clay_Vector2) { mouseX, mouseY }, isMouseDown);
        Clay_RenderCommandArray content = vp_layout();

        // Clearing the background
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // CLAY rendering
        Clay_SDL2_Render(renderer, content, fonts);

        // SDL2 rendering
        SDL_RenderPresent(renderer);
    }

QUIT:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
#endif

int main(void)
{
    // Init application state
    if (vp_init() < 0) return 1;

    int exec_result;

#ifdef RENDERER_RAYLIB
    exec_result = raylib_main();
#endif

#ifdef RENDERER_SDL2
    exec_result = sdl2_main();
#endif

#if 0
#ifdef RENDERER_SDL3
    exec_result = sdl3_main();
#endif
#endif

    vp_destroy();
    return exec_result;
}

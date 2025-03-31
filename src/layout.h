#ifndef LAYOUT_H_
#define LAYOUT_H_

Clay_RenderCommandArray vp_layout(int width, int height)
{
    // Like Raylib, CLAY scope start
    Clay_BeginLayout();

    CLAY({ 
        .layout = { .sizing = { .width = width, .height = height } },
        .backgroundColor = { 18, 18, 18, 255 },
    }) {}

    // CLAY scope end, it returns the commands to render the layout
    return Clay_EndLayout();
}

#endif // LAYOUT_H_

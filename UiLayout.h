#pragma once

#include <dwmapi.h>
#include <vector>

// Structure that defines a color palette. See 
// https://colorhunt.co/palette/525252414141313131ca3e47 for more information.
static class ColorPalette
{
public:
    COLORREF BackgroundColorDarkTheme, ElevatedColorDarkTheme, FrameColorDarkTheme, AccentColorDarkTheme;

    ColorPalette();
} MyColors;

// Class that defines all rectangles within the client area.
static class Forms
{
public:
    struct rectangle {
        RECT rectangle;
        COLORREF color;
    };

    rectangle Canvas, Button1, Button2;

    std::vector<rectangle> allRectangles;

    Forms();
} MyForms;
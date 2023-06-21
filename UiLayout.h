#pragma once

#include <dwmapi.h>

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

    static const int arraySize = 3;
    rectangle allRectangles[arraySize];

    Forms();
} MyForms;
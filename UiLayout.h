#pragma once

#include <dwmapi.h>
#include <vector>

// Structure that defines a color palette. See 
// https://colorhunt.co/palette/525252414141313131ca3e47 for more 
// information.
static class ColorPalette
{
public:
    COLORREF BackgroundColorDarkTheme, ElevatedColorDarkTheme, FrameColorDarkTheme, AccentColorDarkTheme;

    ColorPalette();
} MyColors;

// Class that stores data of user interface objects within the client 
// area.
static class UiObjects
{
public:
    struct Object {
        RECT rectangle;
        COLORREF color;
        LPWSTR objectText;
        int objectType; // 1: Button
    };

    Object Canvas, Button1, Button2, Button3;

    std::vector<Object> Objects;

    UiObjects();
} MyUiObjects;
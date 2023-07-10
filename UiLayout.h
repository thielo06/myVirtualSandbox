#pragma once

#include <dwmapi.h>
#include <vector>

// Structure that defines a color palette. See 
// https://colorhunt.co/palette/525252414141313131ca3e47 and 
// https://colorhunt.co/palette/f8f8f8faebcdf7c873434343 for more 
// information.
static class ColorPalette
{
public:
    COLORREF TextColorDarkTheme, BackgroundColorDarkTheme, ElevatedColorDarkTheme, FrameColorDarkTheme, AccentColorDarkTheme;

    ColorPalette();
} MyColors;

// Class that stores data of user interface objects within the client 
// area.
static class UiObjects
{
public:
    struct Object {
        COLORREF color;
        LPWSTR objectText;
        RECT rectangle;
        int identifier; // 100.. : Buttons
        int objectType; // 0: Canvas, 1: Button
    };

    Object Canvas, Button1, Button2;

    std::vector<Object> Objects;

    UiObjects();
} MyUiObjects;
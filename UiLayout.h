#pragma once

#include <dwmapi.h>
#include <string>
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
    enum ObjectClass { Custom, Button };

    struct Object {
        LPWSTR lpClassName;
        LPWSTR lpWindowName;
        DWORD dwStyle;
        LONG x;
        LONG y;
        LONG nWidth;
        LONG nHeigth;
        HMENU hMenu;
        HWND hObjectWnd;
        ObjectClass objectType;
        COLORREF color;
    };

    // Declare the user interface objects.
    Object Canvas, Output, Button1, CloseApplicationButton, ResetOutputButton;

    // Declare a vector class as a container of pointers to the 
    // "Object"-Elements.
    std::vector<Object*> Objects;

    UiObjects();
} MyObjects;
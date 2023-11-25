#pragma once

#include "Header.h"

#include <vector>

// Structure that defines a color palette. See 
// https://colorhunt.co/palette/525252414141313131ca3e47 and 
// https://colorhunt.co/palette/f8f8f8faebcdf7c873434343 for more 
// information.
static class ColorPalette
{
public:
    COLORREF TextColorDarkTheme,
        BackgroundColorDarkTheme,
        ElevatedColorDarkTheme,
        FrameColorDarkTheme,
        RedAccentDarkTheme,
        BlueAccentDarkTheme,
        YellowAccentDarkTheme;

    ColorPalette();
} MyColors;

// Class that stores data of user interface objects within the client 
// area.
static class UiObjects
{
public:
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
        COLORREF color;
    };

    // Declare the user interface objects.
    Object Canvas, Output, AddPointButton, SelectPointButton, CloseApplicationButton, ResetOutputButton;

    // Initialize the user interface objects control identifiers.
    enum objectControlId
    {
        CanvasId,
        OutputId,
        AddPointButtonId,
        SelectPointButtonId,
        CloseApplicationButtonId,
        ResetOutputButtonId
    };

    // Declare a vector class as a container of pointers to the 
    // "Object"-Elements.
    std::vector<Object*> Objects;

    UiObjects();
} MyObjects;
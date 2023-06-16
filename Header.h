#pragma once

#include <dwmapi.h>
#include <windows.h>
#include <windowsx.h>

#using <System.dll>
#using <System.Xml.dll>

using namespace System;

// Global constants
const long CANVAS_VER_OFFSET = 10;
const long CANVAS_HOR_OFFSET = 10;

const long CANVAS_WIDTH = 640;
const long CANVAS_HEIGHT = 480;

#pragma region Creation of Classes and Objects
// Structure that defines a color palette. See 
// https://colorhunt.co/palette/525252414141313131ca3e47 for more information.
class ColorPalette
{
public:
    COLORREF BackgroundColorDarkTheme, ElevatedColorDarkTheme, FrameColorDarkTheme, AccentColorDarkTheme;

    ColorPalette() {
        BackgroundColorDarkTheme = RGB(65, 65, 65);

        ElevatedColorDarkTheme = RGB(49, 49, 49);

        FrameColorDarkTheme = RGB(82, 82, 82);

        AccentColorDarkTheme = RGB(202, 62, 71);
    }
};
ColorPalette MyColors;

// Structure that defines all rectangles within the client area.
class Rectangles
{
public:
    RECT CanvasArea, CanvasFrame;

    Rectangles() {
        CanvasArea = {
            CANVAS_HOR_OFFSET,
            CANVAS_VER_OFFSET,
            CANVAS_HOR_OFFSET + CANVAS_WIDTH,
            CANVAS_VER_OFFSET + CANVAS_HEIGHT
        };
        
        CanvasFrame = {
            CanvasArea.left - 1,
            CanvasArea.top - 1,
            CanvasArea.right + 1,
            CanvasArea.bottom + 1
        };
    }
};
Rectangles MyRectangles;
#pragma endregion

void DrawPoint(HWND hWnd, POINT pt, COLORREF penColor) {
    Diagnostics::Debug::Write(pt.x + " " + pt.y + "\n");

    HDC hDeviceContext;

    hDeviceContext = GetDC(hWnd);

    SetPixel(hDeviceContext, pt.x, pt.y, penColor);
}

bool Contains(RECT rect, POINT pt) {
    if (pt.x < rect.left || pt.x >= rect.right) {
        return false;
    }
    if (pt.y < rect.top || pt.y >= rect.bottom) {
        return false;
    }
    return true;
}
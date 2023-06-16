#pragma once

#include <dwmapi.h>
#include <windows.h>

#using <System.dll>
#using <System.Xml.dll>

using namespace System;

// Global constants
const long CANVAS_VER_OFFSET = 10;
const long CANVAS_HOR_OFFSET = 10;

const long CANVAS_WIDTH = 640;
const long CANVAS_HEIGHT = 480;

/// <summary>
/// Color Palette https://colorhunt.co/palette/525252414141313131ca3e47
/// </summary>
class ColorPalette
{
    public:
        COLORREF BackgroundColorDarkTheme, ElevatedColorDarkTheme, FrameColorDarkTheme, AccentColorDarkTheme;

        // TODO: Update Color Values
        ColorPalette() {
            BackgroundColorDarkTheme = RGB(25, 26, 25);

            ElevatedColorDarkTheme = RGB(15, 16, 15);

            FrameColorDarkTheme= RGB(40, 41, 40);

            AccentColorDarkTheme= RGB(78, 159, 61);
        }
};

RECT CanvasArea = {
    CANVAS_HOR_OFFSET,
    CANVAS_VER_OFFSET,
    CANVAS_HOR_OFFSET + CANVAS_WIDTH,
    CANVAS_VER_OFFSET + CANVAS_HEIGHT
};

RECT CanvasFrame = {
    CanvasArea.left - 1,
    CanvasArea.top - 1,
    CanvasArea.right + 1,
    CanvasArea.bottom + 1
};

void DrawPoint(HWND hWnd, POINT pt, COLORREF penColor) {
    Diagnostics::Debug::Write(pt.x + " " + pt.y + "\n");

    HDC hDeviceContext;

    hDeviceContext = GetDC(hWnd);

    SetPixel(hDeviceContext, pt.x, pt.y, penColor);
};

bool RectContains(RECT rect, POINT pt) {
    if (pt.x < rect.left || pt.x >= rect.right) {
        return false;
    }
    if (pt.y < rect.top || pt.y >= rect.bottom) {
        return false;
    }
    return true;
}
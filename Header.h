#pragma once

#include <dwmapi.h>
#include <windows.h>
#include <windowsx.h>

#using <System.dll>
#using <System.Xml.dll>

using namespace System;

// Global constants
const int CANVAS_VER_OFFSET = 10;
const int CANVAS_HOR_OFFSET = 10;
const int CANVAS_WIDTH = 640;
const int CANVAS_HEIGHT = 480;

const int BUTTON_1_WIDTH = 100;
const int BUTTON_1_HEIGTH = 30;

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
} MyColors;

// Class that defines all rectangles within the client area.
class Forms
{
public:
    struct rectangle {
        RECT rectangle;
        COLORREF color;
    };

    rectangle Canvas, Button1, Button2;

    static const int arraySize = 3;
    rectangle allRectangles[arraySize];

    Forms() {
        Canvas.rectangle = {
            CANVAS_HOR_OFFSET,
            CANVAS_VER_OFFSET,
            CANVAS_HOR_OFFSET + CANVAS_WIDTH,
            CANVAS_VER_OFFSET + CANVAS_HEIGHT
        };
        Canvas.color = MyColors.ElevatedColorDarkTheme;
        allRectangles[0] = Canvas;

        Button1.rectangle = {
            CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10,
            CANVAS_VER_OFFSET,
            CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10 + BUTTON_1_WIDTH,
            CANVAS_VER_OFFSET + BUTTON_1_HEIGTH
        };
        Button1.color = MyColors.ElevatedColorDarkTheme;
        allRectangles[1] = Button1;

        Button2.rectangle = {
            CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10,
            CANVAS_VER_OFFSET + BUTTON_1_HEIGTH + 10,
            CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10 + BUTTON_1_WIDTH,
            CANVAS_VER_OFFSET + BUTTON_1_HEIGTH + 10 + BUTTON_1_HEIGTH
        };
        Button2.color = MyColors.ElevatedColorDarkTheme;
        allRectangles[2] = Button2;
    }
} MyForms;

void FrameRectangle(HDC hDeviceContext, RECT rectangle, HBRUSH hBrush) {
    RECT frameRect;

    frameRect.left = rectangle.left - 1;
    frameRect.top = rectangle.top - 1;
    frameRect.right = rectangle.right + 1;
    frameRect.bottom = rectangle.bottom + 1;

    FrameRect(
        hDeviceContext,
        &frameRect,
        hBrush
    );
}

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
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
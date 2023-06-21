#pragma once

#include "Header.h"

class AppFunctions
{
public:
    static void FrameRectangle(HDC hDeviceContext, RECT rectangle, HBRUSH hBrush);

    static void DrawPoint(HWND hWnd, POINT pt, COLORREF penColor);

    static bool Contains(RECT rect, POINT pt);
};
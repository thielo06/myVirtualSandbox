#pragma once

#include "Header.h"

namespace AppFunctions
{
    void FrameRectangle(HDC hDeviceContext, RECT rectangle, HBRUSH hBrush);

    void DrawPoint(HWND hWnd, POINT pt, COLORREF penColor);

    bool Contains(RECT rect, POINT pt);
};
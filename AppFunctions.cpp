#include "AppFunctions.h"
#include "Header.h"

void AppFunctions::FrameRectangle(HDC hDeviceContext, RECT rectangle, HBRUSH hBrush) {
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

void AppFunctions::DrawPoint(HWND hWnd, POINT pt, COLORREF penColor) {
    Diagnostics::Debug::Write(pt.x + " " + pt.y + "\n");

    HDC hDeviceContext;

    hDeviceContext = GetDC(hWnd);

    SetPixel(hDeviceContext, pt.x, pt.y, penColor);
}

bool AppFunctions::Contains(RECT rect, POINT pt) {
    if (pt.x < rect.left || pt.x >= rect.right) {
        return false;
    }
    if (pt.y < rect.top || pt.y >= rect.bottom) {
        return false;
    }
    return true;
}
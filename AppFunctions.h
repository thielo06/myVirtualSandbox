#pragma once

#include "Header.h"

namespace AppFunctions
{
    void InitializeXmlDocument();

    void DrawPoint(HWND hWnd, POINT pt, COLORREF penColor);

    XmlElement^ SerializePoint(XmlDocument^ xmlDoc, POINT point);
};
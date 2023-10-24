#pragma once

#include "Header.h"

namespace AppFunctions
{
    int DrawBitmap(INT bitmapId, HDC hDeviceContext, LONG bitmapX, LONG bitmapY, LPWSTR bitmapOrigin);

    int SearchPointXmlDocument(INT32 xValue, INT32 yValue);

    void ResetSelection();

    void AddPoint(POINT point);

    void UpdatePoints(HDC hDeviceContext, int pointId=-1);

    POINT SelectPoint(int& pointId);

    XmlDocument^ InitializeXmlDocument();

    XmlElement^ SerializePoint(POINT point);
};
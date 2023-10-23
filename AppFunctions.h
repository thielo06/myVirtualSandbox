#pragma once

#include "Header.h"

namespace AppFunctions
{
    int DrawBitmap(INT bitmapId, HDC hDeviceContext, LONG bitmapX, LONG bitmapY, LPWSTR bitmapOrigin);

    int SearchPointXmlDocument(POINT point);

    void ResetSelection();

    void SelectPoint(int pointId);

    void AddPoint(POINT point);

    void UpdatePoints(HDC hDeviceContext, int pointId = -1);

    XmlDocument^ InitializeXmlDocument();

    XmlElement^ SerializePoint(POINT point);
};
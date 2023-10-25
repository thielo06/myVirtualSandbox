#pragma once

#include "Header.h"

namespace AppFunctions
{
    int DrawBitmap(INT bitmapId, HDC hDeviceContext, LONG bitmapX, LONG bitmapY, LPWSTR bitmapOrigin);

    int GetSelectionState(int pointId);

    int SearchPointXmlDocument(INT32 xValue, INT32 yValue);

    void ResetSelection();

    void AddPoint(POINT point);

    void UpdatePoints(HDC hDeviceContext, int pointId=-1);

    POINT UpdateSelectionState(int pointId, int selectionState);

    XmlDocument^ InitializeXmlDocument();

    XmlElement^ SerializePoint(POINT point);
};
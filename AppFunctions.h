#pragma once

#include "Header.h"

namespace AppFunctions
{
    int DrawBitmap(INT bitmapId, HDC hDeviceContext, LONG bitmapX, LONG bitmapY, LPWSTR bitmapOrigin);

    int SearchPointXmlDocument(POINT point);

    void InitializeXmlDocument();

    void ResetSelectionState();

    void StorePoint(POINT point);

    void UpdatePoints(HDC hDeviceContext);

    XmlElement^ SerializePoint(XmlDocument^ xmlDoc, POINT point);
};
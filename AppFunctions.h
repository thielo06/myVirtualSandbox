#pragma once

#include "Header.h"

namespace AppFunctions
{
    void InitializeXmlDocument();

    int DrawBitmap(INT bitmapId, HDC hDeviceContext, LONG bitmapX, LONG bitmapY, LPWSTR bitmapOrigin);

    void StorePoint(POINT point);

    XmlElement^ SerializePoint(XmlDocument^ xmlDoc, POINT point);

    void DeserializePoints(HDC hDeviceContext);
};
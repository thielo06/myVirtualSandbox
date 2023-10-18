#pragma once

#include "Header.h"

namespace AppFunctions
{
    int DrawBitmap(INT bitmapId, HDC hDeviceContext, LONG bitmapX, LONG bitmapY, LPWSTR bitmapOrigin);

    void DeserializePoints(HDC hDeviceContext);

    void InitializeXmlDocument();

    void StorePoint(POINT point);

    XmlElement^ SerializePoint(XmlDocument^ xmlDoc, POINT point);
};
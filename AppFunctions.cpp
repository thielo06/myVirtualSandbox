#include "AppFunctions.h"
#include "Header.h"

int AppFunctions::DrawBitmap(INT bitmapId, HDC hDeviceContext, LONG bitmapX, LONG bitmapY, LPWSTR bitmapOrigin = L"c") {
    BITMAP bitmap;
    HBITMAP hBitmap;
    HDC hMemoryDeviceContext;
    HGDIOBJ hOldBitmap;
    INT status, bitmapOriginX, bitmapOriginY;
    LPWSTR bitmapResource;

    bitmapResource = MAKEINTRESOURCE(bitmapId);

    // Create a handle from the bitmap resource.
    hBitmap = LoadBitmapW(
        GetModuleHandle(NULL),
        bitmapResource
    );

    // Create a compatible device context in reference 
    // to the device context of item structure.
    hMemoryDeviceContext = CreateCompatibleDC(hDeviceContext);

    // Select the bitmap handle to the memory device 
    // context and store a copy of it in a variable.
    // The return value is, if the funtion succeeds and the 
    // selected object is not a region, is a handle to the 
    // object that is being replaced.
    hOldBitmap = SelectObject(hMemoryDeviceContext, hBitmap);

    // Read graphical information from the handle 
    // and write it to the buffer at specified 
    // location.
    bitmap = {};
    GetObject(hBitmap, sizeof(bitmap), &bitmap);

    bitmapOriginX = bitmapX - bitmap.bmWidth / 2;
    bitmapOriginY = bitmapY - bitmap.bmHeight / 2;

    if (!lstrcmpW(bitmapOrigin, L"nw")) {
        bitmapOriginX = bitmapX;
        bitmapOriginY = bitmapY;
    }

    // Perform a bit block transfer between the source 
    // device context and the device context of the 
    // item structure.
    status = BitBlt(
        hDeviceContext,
        bitmapOriginX, bitmapOriginY,
        bitmap.bmWidth,
        bitmap.bmHeight,
        hMemoryDeviceContext,
        0, 0,
        SRCCOPY
    );

    // Select the original bitmap handle to the source 
    // device context and delete the object.
    SelectObject(hMemoryDeviceContext, hOldBitmap);
    DeleteDC(hMemoryDeviceContext);

    return status;
}

void AppFunctions::DeserializePoints(HDC hDeviceContext) {
    // Load data cache file and write point coordinates to it.
    XmlDocument^ xmlDoc = gcnew XmlDocument();
    xmlDoc->Load("dataCache.xml");

    XmlNodeList^ elemList = xmlDoc->GetElementsByTagName("point");

    if (elemList->Count) {
        for (int i = 0; i < elemList->Count; i++) {
            INT32 xValue, yValue;
            POINT point;

            Int32::TryParse(elemList[i]->Attributes[0]->Value, xValue);
            Int32::TryParse(elemList[i]->Attributes[1]->Value, yValue);

            point = {
                xValue,
                yValue
            };

            DrawBitmap(IDB_BITMAP3, hDeviceContext, point.x, point.y);
        }
    }
}

void AppFunctions::InitializeXmlDocument() {
    XmlDocument^ doc = gcnew XmlDocument();
    doc->LoadXml("<root></root>");
    doc->Save("dataCache.xml");
}

void AppFunctions::StorePoint(POINT point) {
    // Load data cache file and write point coordinates to it.
    XmlDocument^ xmlDoc = gcnew XmlDocument();
    xmlDoc->Load("dataCache.xml");

    XmlElement^ xmlPoint;

    xmlPoint = AppFunctions::SerializePoint(xmlDoc, point);

    xmlDoc->DocumentElement->AppendChild(xmlPoint);

    xmlDoc->Save("dataCache.xml");
}

XmlElement^ AppFunctions::SerializePoint(XmlDocument^ xmlDoc, POINT point) {
    XmlElement^ xmlPoint = xmlDoc->CreateElement("point");

    // New elements are "pushed" into the XML-Structure from above, 
    // respectively attributes are "pushed" from the left. Hence it is 
    // necessary to set the attribute that shall occure at the very 
    // left at first.
    xmlPoint->SetAttribute("x", point.x.ToString());
    xmlPoint->SetAttribute("y", point.y.ToString());

    return xmlPoint;
}

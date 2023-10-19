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

void AppFunctions::InitializeXmlDocument() {
    XmlDocument^ xmlDoc = gcnew XmlDocument();
    String^ fileName = gcnew String(STORAGE);

    xmlDoc->Load(fileName);

    // Load the XML document from the specified string and save it to 
    // an URL.
    xmlDoc->LoadXml("<root></root>");
    xmlDoc->Save(fileName);
}

// Returns 0 if point is found in XML Document.
int AppFunctions::SearchPointXmlDocument(POINT point) {
    XmlDocument^ xmlDoc = gcnew XmlDocument();
    String^ fileName = gcnew String(STORAGE);

    int status = 1;

    // Load the XML document from the specified URL.
    xmlDoc->Load(fileName);

    XmlNodeList^ nodeList = xmlDoc->GetElementsByTagName("point");

    if (nodeList->Count) {
        for (int i = 0; i < nodeList->Count; i++) {
            XmlNode^ node = nodeList[i];
            XmlElement^ element = (XmlElement^)node;

            INT32 xValue, yValue;

            Int32::TryParse(node->Attributes[0]->Value, xValue);
            Int32::TryParse(node->Attributes[1]->Value, yValue);

            if (xValue == point.x && yValue == point.y) {
                element->SetAttribute("selectionState", "1");
                xmlDoc->Save(fileName);

                status = 0;
            }
        }
    }

    return status;
};

void AppFunctions::StorePoint(POINT point) {
    // Load data cache file and write point coordinates to it.
    XmlDocument^ xmlDoc = gcnew XmlDocument();
    String^ fileName = gcnew String(STORAGE);

    xmlDoc->Load(fileName);

    XmlElement^ xmlPoint;

    xmlPoint = AppFunctions::SerializePoint(xmlDoc, point);

    xmlDoc->DocumentElement->AppendChild(xmlPoint);

    xmlDoc->Save(fileName);
}

void AppFunctions::UpdatePoints(HDC hDeviceContext) {
    // Load data storage file and draw all points to handle device 
    // context which is referring to the canvas.
    XmlDocument^ xmlDoc = gcnew XmlDocument();
    String^ fileName = gcnew String(STORAGE);

    INT32 xValue, yValue;
    POINT point;

    int selectionState;

    xmlDoc->Load(fileName);

    XmlNodeList^ nodeList = xmlDoc->GetElementsByTagName("point");

    if (nodeList->Count) {
        for (int i = 0; i < nodeList->Count; i++) {
            XmlNode^ node = nodeList[i];

            Int32::TryParse(node->Attributes[0]->Value, xValue);
            Int32::TryParse(node->Attributes[1]->Value, yValue);
            Int32::TryParse(node->Attributes[2]->Value, selectionState);

            point = {
                xValue,
                yValue
            };

            switch (selectionState) {
                case 0:
                {
                    DrawBitmap(IDB_BITMAP3, hDeviceContext, point.x, point.y);

                    break;
                }
                case 1:
                {
                    DrawBitmap(IDB_BITMAP8, hDeviceContext, point.x, point.y);

                    break;
                }
            }

        }
    }
}

void AppFunctions::ResetSelectionState() {
    XmlDocument^ xmlDoc = gcnew XmlDocument();
    String^ fileName = gcnew String(STORAGE);

    int status = 1;

    // Load the XML document from the specified URL.
    xmlDoc->Load(fileName);

    XmlNodeList^ nodeList = xmlDoc->GetElementsByTagName("point");

    if (nodeList->Count) {
        for (int i = 0; i < nodeList->Count; i++) {
            XmlNode^ node = nodeList[i];
            XmlElement^ element = (XmlElement^)node;

            element->SetAttribute("selectionState", "0");
            xmlDoc->Save(fileName);
        }
    }
}

XmlElement^ AppFunctions::SerializePoint(XmlDocument^ xmlDoc, POINT point) {
    XmlElement^ element = xmlDoc->CreateElement("point");

    // New elements are "pushed" into the XML-Structure from above, 
    // respectively attributes are "pushed" from the left. Hence it is 
    // necessary to set the attribute that shall occure at the very 
    // left at first.
    element->SetAttribute("x", point.x.ToString());
    element->SetAttribute("y", point.y.ToString());
    element->SetAttribute("selectionState", "0");

    return element;
}
#include "AppFunctions.h"
#include "Header.h"

// Initially define tool state as empty.
ToolState CurrentToolState = ToolState::empty;

int mouseHover = -1;

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

    DeleteObject(hBitmap);

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

// Returns pointId if point is found in XML Document, -1 if not.
int AppFunctions::SearchPointXmlDocument(INT32 xValue, INT32 yValue) {
    XmlDocument^ xmlDoc = XmlStorage::XmlDocument;

    // Assign -1 as a default to the return value.
    int pointId = -1;

    XmlNodeList^ nodeList = xmlDoc->GetElementsByTagName("point");

    if (nodeList->Count) {
        for (int i = 0; i < nodeList->Count; i++) {
            XmlNode^ node = nodeList[i];
            XmlElement^ element = (XmlElement^)node;

            INT32 xCompare, yCompare;

            Int32::TryParse(node->Attributes[1]->Value, xCompare);
            Int32::TryParse(node->Attributes[2]->Value, yCompare);

            if (xValue >= xCompare - 1 && xValue <= xCompare + 1) {
                if (yValue >= yCompare - 1 && yValue <= yCompare + 1) {
                    Int32::TryParse(node->Attributes[0]->Value, pointId);
                }
            }
        }
    }

    return pointId;
};

void AppFunctions::ResetSelection() {
    XmlDocument^ xmlDoc = XmlStorage::XmlDocument;
    XmlNodeList^ nodeList = xmlDoc->GetElementsByTagName("point");
    String^ fileName = XmlStorage::FileName;

    int status = 1;

    if (nodeList->Count) {
        for (int i = 0; i < nodeList->Count; i++) {
            XmlNode^ node = nodeList[i];
            XmlElement^ element = (XmlElement^)node;

            element->SetAttribute("selectionState", "0");

            xmlDoc->Save(fileName);
        }
    }
}

void AppFunctions::AddPoint(POINT point) {
    XmlDocument^ xmlDoc = XmlStorage::XmlDocument;
    XmlElement^ xmlElement;

    xmlElement = AppFunctions::SerializePoint(point);

    xmlDoc->DocumentElement->AppendChild(xmlElement);
    xmlDoc->Save(XmlStorage::FileName);
}

void AppFunctions::UpdatePoints(HDC hDeviceContext, int pointId) {
    // Load data storage file and draw all points to handle device 
    // context which is referring to the canvas.
    XmlDocument^ xmlDoc = XmlStorage::XmlDocument;
    XmlElement^ xmlElement;

    INT32 xValue, yValue, selectionState;

    if (pointId!=-1) {
        xmlElement = xmlDoc->GetElementById(pointId.ToString());

        Int32::TryParse(xmlElement->Attributes[1]->Value, xValue);
        Int32::TryParse(xmlElement->Attributes[2]->Value, yValue);
        Int32::TryParse(xmlElement->Attributes[3]->Value, selectionState);

        switch (selectionState) {
            case 0: // not selected
            {
                DrawBitmap(IDB_BITMAP3, hDeviceContext, xValue, yValue);

                break;
            }
            case 1: // hovering
            {
                DrawBitmap(IDB_BITMAP9, hDeviceContext, xValue, yValue);

                break;
            }
            case 2: // selected
            {
                DrawBitmap(IDB_BITMAP8, hDeviceContext, xValue, yValue);

                break;
            }
        }
    } else {
        XmlNodeList^ nodeList = xmlDoc->GetElementsByTagName("point");

        if (nodeList->Count) {
            for (int i = 0; i < nodeList->Count; i++) {
                xmlElement = (XmlElement^)nodeList[i];

                Int32::TryParse(xmlElement->Attributes[1]->Value, xValue);
                Int32::TryParse(xmlElement->Attributes[2]->Value, yValue);
                Int32::TryParse(xmlElement->Attributes[3]->Value, selectionState);

                switch (selectionState) {
                    case 0: // not selected
                    {
                        DrawBitmap(IDB_BITMAP3, hDeviceContext, xValue, yValue);

                        break;
                    }
                    case 1: // hovering
                    {
                        DrawBitmap(IDB_BITMAP9, hDeviceContext, xValue, yValue);

                        break;
                    }
                    case 2: // selected
                    {
                        DrawBitmap(IDB_BITMAP8, hDeviceContext, xValue, yValue);

                        break;
                    }
                }
            }
        }
    }
}

POINT AppFunctions::UpdateSelectionState(int pointId, int selectionState) {
    XmlDocument^ xmlDoc = XmlStorage::XmlDocument;
    XmlElement^ xmlElement;

    INT32 xValue, yValue;
    POINT point;

    xmlElement = xmlDoc->GetElementById(pointId.ToString());
    xmlElement->SetAttribute("selectionState", selectionState.ToString());
    xmlDoc->Save(XmlStorage::FileName);

    Int32::TryParse(xmlElement->Attributes[1]->Value, xValue);
    Int32::TryParse(xmlElement->Attributes[2]->Value, yValue);

    point = {
        (LONG)xValue,
        (LONG)yValue
    };

    return point;
};

XmlDocument^ AppFunctions::InitializeXmlDocument() {
    XmlDocument^ xmlDoc = gcnew XmlDocument();
    XmlDocumentType^ xmlDoctype;

    xmlDoctype = xmlDoc->CreateDocumentType(
        // Name of the document type
        "root",
        nullptr, nullptr,
        // DTD internal subset of the document type
        "<!ELEMENT root (point)*>"
        "<!ELEMENT point EMPTY>"
        "<!ATTLIST point"
        " id ID #REQUIRED"
        " selectionstate CDATA #REQUIRED"
        " y CDATA #REQUIRED"
        " x CDATA #REQUIRED"
        ">"
    );
    xmlDoc->AppendChild(xmlDoctype);

    xmlDoc->AppendChild(xmlDoc->CreateElement("root"));
    xmlDoc->Save(XmlStorage::FileName);

    return xmlDoc;
}

XmlElement^ AppFunctions::SerializePoint(POINT point) {
    XmlDocument^ xmlDoc = XmlStorage::XmlDocument;
    XmlElement^ element = xmlDoc->CreateElement("point");
    XmlNodeList^ nodeList;

    nodeList = xmlDoc->GetElementsByTagName("point");

    int idCount = nodeList->Count;

    // New elements are "pushed" into the XML-Structure from above, 
    // respectively attributes are "pushed" from the left. Hence it is 
    // necessary to set the attribute that shall occure at the very 
    // left at first.
    element->SetAttribute("id", idCount.ToString());
    element->SetAttribute("x", point.x.ToString());
    element->SetAttribute("y", point.y.ToString());
    element->SetAttribute("selectionState", "0");

    return element;
}
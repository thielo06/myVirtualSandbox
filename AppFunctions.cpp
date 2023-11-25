#include "AppFunctions.h"

// Initialize global variables.
ToolState CurrentToolState = ToolState::empty;
bool prevPointFlag = false;
int prevPointId = -1;

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
int AppFunctions::SearchPoint(INT32 xValue, INT32 yValue) {
    // Assign -1 as a default to the return value.
    int pointId = -1;

    XmlNodeList^ nodeList = XmlStorage::XmlDocument->GetElementsByTagName("point");

    if (nodeList->Count) {
        for (int i = 0; i < nodeList->Count; i++) {
            XmlNode^ node = nodeList[i];
            XmlElement^ element = (XmlElement^)node;

            INT32 xCompare, yCompare;

            Int32::TryParse(node->Attributes[1]->Value, xCompare);
            Int32::TryParse(node->Attributes[2]->Value, yCompare);

            if (xValue >= xCompare - 2 && xValue <= xCompare + 2) {
                if (yValue >= yCompare - 2 && yValue <= yCompare + 2) {
                    Int32::TryParse(node->Attributes[0]->Value, pointId);
                }
            }
        }
    }

    return pointId;
}

void AppFunctions::ResetSelection() {
    XmlNodeList^ nodeList = XmlStorage::XmlDocument->GetElementsByTagName("point");
    String^ fileName = XmlStorage::FileName;

    int status = 1;

    if (nodeList->Count) {
        for (int i = 0; i < nodeList->Count; i++) {
            XmlNode^ node = nodeList[i];
            XmlElement^ element = (XmlElement^)node;

            element->SetAttribute("selectionState", "0");
        }
    }

    XmlStorage::XmlDocument->Save(fileName);
}

// Serialize an XML-Element from a POINT-Structure and append it as a child to 
// global XML-Document.
void AppFunctions::AddPoint(POINT point) {
    XmlElement^ xmlElement = AppFunctions::SerializePoint(point);

    XmlStorage::XmlDocument->DocumentElement->AppendChild(xmlElement);
    XmlStorage::XmlDocument->Save(XmlStorage::FileName);
}

void AppFunctions::UpdatePoints(HDC hDeviceContext, int pointId) {
    // Load data storage file and draw all points to handle device 
    // context which is referring to the canvas.
    XmlDocument^ xmlDoc = XmlStorage::XmlDocument;
    XmlElement^ xmlElement;

    INT32 xValue, yValue, selectionState;

    if (pointId != -1) {
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
    }
    else {
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

int AppFunctions::GetSelectionState(int pointId) {
    XmlDocument^ xmlDoc = XmlStorage::XmlDocument;
    XmlElement^ xmlElement;

    int selectionState;

    xmlElement = xmlDoc->GetElementById(pointId.ToString());

    Int32::TryParse(xmlElement->Attributes[3]->Value, selectionState);

    return selectionState;
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
}

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

// Create an XML-Element and assign various attributes to it.
XmlElement^ AppFunctions::SerializePoint(POINT point) {
    XmlElement^ element = XmlStorage::XmlDocument->CreateElement("point");
    XmlNodeList^ nodeList = XmlStorage::XmlDocument->GetElementsByTagName("point");

    element->SetAttribute("id", nodeList->Count.ToString());
    element->SetAttribute("x", point.x.ToString());
    element->SetAttribute("y", point.y.ToString());
    element->SetAttribute("selectionState", "0");

    return element;
}

void AppFunctions::TextOutput(HWND hOutputWnd, LPWSTR tempTextBuffer) {
    LPWSTR textOutput, wndTextBuffer;

    int textLength, wndTextLength;

    // Create a buffer with length of the window text.
    wndTextLength = GetWindowTextLength(hOutputWnd) + 1;
    wndTextBuffer = new wchar_t[wndTextLength];

    // Get the window text and write it to the buffer.
    GetWindowText(hOutputWnd, wndTextBuffer, wndTextLength);

    // If the length of the window text is bigger than 
    // one, the window text is not empty and it is 
    // concatenated with the value of the temporary text 
    // buffer.
    // If it is equal to one it means that it is empty, so 
    // the text output is just the value of the tempory 
    // text buffer.
    if (wndTextLength > 1) {
        // The length of the new text is the length of the 
        // window text in addition to the tempory text 
        // buffer.
        // The array size is increased by three 
        // characters, two for a linebreak "\r\n" and one 
        // for the null terminator "\0".
        textLength = wndTextLength + 2 + (int)wcslen(tempTextBuffer) + 1;
        textOutput = new wchar_t[textLength];

        wsprintfW(textOutput, L"%s\r\n%s", wndTextBuffer, tempTextBuffer);
    }
    else {
        textLength = (int)wcslen(tempTextBuffer) + 1;
        textOutput = new wchar_t[textLength];

        wsprintfW(textOutput, L"%s", tempTextBuffer);
    }

    SendMessage(hOutputWnd, WM_SETTEXT, NULL, (LPARAM)textOutput);
}
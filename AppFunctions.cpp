#include "AppFunctions.h"

// Initialize global variables.
ToolState CurrentToolState = ToolState::empty;
bool prevPointFlag = false;
int prevPointId = -1;

AppFunctions::DataStorage MyDataStorage;

AppFunctions::DataStorage::DataStorage() {
    CanvasData = {};
};

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

// Returns point id if it is found in data storage, -1 if not.
int AppFunctions::SearchPoint(int xValue, int yValue) {
    int result = -1;
    
    int n = MyDataStorage.CanvasData.size();
    
    if (n != 0) {
        for (int i = 0; i < n; i++) {
            DataStorage::ElementData elementData = MyDataStorage.CanvasData[i];

            int xCompare, yCompare;

            xCompare = elementData.position.x;
            yCompare = elementData.position.y;

            if (xValue >= xCompare - 2 && xValue <= xCompare + 2) {
                if (yValue >= yCompare - 2 && yValue <= yCompare + 2) {
                    result = elementData.id;
                }
            }
        }
    } else {

    }

    return result;
}

void AppFunctions::ResetSelection() {
    int n = MyDataStorage.CanvasData.size();

    if (n != 0) {
        for (int i = 0; i < n; i++) {
            MyDataStorage.CanvasData[i].selectionState = 0;
        }
    } else {

    }
}

void AppFunctions::AddPoint(POINT point) {
    AppFunctions::DataStorage::ElementData elementData = {
        MyDataStorage.CanvasData.size(),
        "POINT",
        0,
        point
    };

    MyDataStorage.CanvasData.push_back(elementData);
}

void AppFunctions::UpdatePoints(HDC hDeviceContext, int elementId) {
    // Load data storage file and draw all points to handle device 
    // context which is referring to the canvas.
    AppFunctions::DataStorage::ElementData elementData;

    int bitmapId, selectionState, xValue, yValue;

    if (elementId != -1) {
        elementData = MyDataStorage.CanvasData[elementId];

        xValue = elementData.position.x;
        yValue = elementData.position.y;

        switch (elementData.selectionState) {
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
        int n = MyDataStorage.CanvasData.size();

        if (n != 0) {
            for (int i = 0; i < n; i++) {
                DataStorage::ElementData elementData = MyDataStorage.CanvasData[i];

                int xValue, yValue;

                xValue = elementData.position.x;
                yValue = elementData.position.y;

                switch (elementData.selectionState) {
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
        } else {

        }
    }
}

int AppFunctions::GetSelectionState(int elementId) {

    return MyDataStorage.CanvasData[elementId].selectionState;
}

POINT AppFunctions::UpdateSelectionState(int elementId, int selectionState) {
    int xValue, yValue;

    POINT point;

    MyDataStorage.CanvasData[elementId].selectionState = selectionState;

    point = {
        MyDataStorage.CanvasData[elementId].position.x,
        MyDataStorage.CanvasData[elementId].position.y
    };

    return point;
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
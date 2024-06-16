#include "AppFunctions.h"

// Initialize global variables.
ToolState CurrentToolState = ToolState::Empty;

bool activePointFlag = false;
int activePointId = -1;

AppFunctions::DataStorage MyDataStorage;

AppFunctions::DataStorage::DataStorage() {
    CanvasData = {};
};

int AppFunctions::DrawBitmap(
    HDC hDeviceContext,
    INT bitmapId,
    LONG bitmapX,
    LONG bitmapY,
    AppFunctions::Alignment bitmapOrigin
) {
    BITMAP bitmap;

    int bitmapOriginX, bitmapOriginY;

    // Create a handle as a reference to the bitmap resource.
    HBITMAP hBitmap = LoadBitmap(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(bitmapId)
    );

    // Bitmap data of the referenced handle is written to the buffer.
    GetObject(hBitmap, sizeof(bitmap), &bitmap);

    HDC hMemoryDeviceContext = CreateCompatibleDC(hDeviceContext);

    SelectObject(hMemoryDeviceContext, hBitmap);

    switch (bitmapOrigin) {
        case (AppFunctions::Alignment::NorthWest):
        {
            bitmapOriginX = bitmapX;
            bitmapOriginY = bitmapY;

            break;
        }
        case (AppFunctions::Alignment::Center):
        {
            //...
        }
        default: {
            bitmapOriginX = bitmapX - bitmap.bmWidth / 2;
            bitmapOriginY = bitmapY - bitmap.bmHeight / 2;
            
            break;
        }
    }

    BitBlt(
        hDeviceContext,
        bitmapOriginX,
        bitmapOriginY,
        bitmap.bmWidth,
        bitmap.bmHeight,
        hMemoryDeviceContext,
        0, 0,
        SRCCOPY
    );

    DeleteObject(hBitmap);
    DeleteDC(hMemoryDeviceContext);

    return 0;
};

int AppFunctions::DrawCanvasBitmap(
    HDC hDeviceContext,
    int* objectIdArray,
    int objectIdArraySize,
    AppFunctions::Alignment bitmapOrigin
) {
    for (int i = 0; i < objectIdArraySize; i++) {
        BITMAP bitmap;

        int bitmapId, bitmapX, bitmapY, bitmapOriginX, bitmapOriginY;

        // Get the object ID of the current element of the array and create a 
        // copy of the corresponding object.
        int objectId = objectIdArray[i];
        AppFunctions::DataStorage::ObjectData object = MyDataStorage.CanvasData[objectId];

        // Define the bitmap to be drawn in relation to the selection state 
        // of the object.
        switch (object.selectionState) {
            case SelectionState::Hovering:
            {
                bitmapId = IDB_BITMAP9;

                break;
            }
            case SelectionState::Selected:
            {
                bitmapId = IDB_BITMAP8;

                break;
            }
            case SelectionState::Empty:
            {
                // ...
            }
            default:
            {
                bitmapId = IDB_BITMAP3;

                break;
            }
        }

        // Define the position where to be drawn in relation to the object´s position.
        bitmapX = object.position.x;
        bitmapY = object.position.y;

        // Create a handle as a reference to the bitmap resource.
        HBITMAP hBitmap = LoadBitmap(
            GetModuleHandle(NULL),
            MAKEINTRESOURCE(bitmapId)
        );

        // Bitmap data of the referenced handle is written to the buffer.
        GetObject(hBitmap, sizeof(bitmap), &bitmap);

        HDC hMemoryDeviceContext = CreateCompatibleDC(hDeviceContext);

        SelectObject(hMemoryDeviceContext, hBitmap);

        switch (bitmapOrigin) {
            case (AppFunctions::Alignment::NorthWest):
            {
                bitmapOriginX = bitmapX;
                bitmapOriginY = bitmapY;

                break;
            }
            case (AppFunctions::Alignment::Center):
            {
                //...
            }
            default: {
                bitmapOriginX = bitmapX - bitmap.bmWidth / 2;
                bitmapOriginY = bitmapY - bitmap.bmHeight / 2;

                break;
            }
        }

        BitBlt(
            hDeviceContext,
            bitmapOriginX,
            bitmapOriginY,
            bitmap.bmWidth,
            bitmap.bmHeight,
            hMemoryDeviceContext,
            0, 0,
            SRCCOPY
        );

        DeleteObject(hBitmap);
        DeleteDC(hMemoryDeviceContext);
    }

    return 0;
};

// Returns point id if it is found in data storage, -1 if not.
int AppFunctions::SearchDataStorage(POINT point) {
    
    int n, result, xValue, yValue;

    n = MyDataStorage.CanvasData.size();
    result = -1;
    xValue = point.x;
    yValue = point.y;
    
    if (n != 0) {
        for (int i = 0; i < n; i++) {
            DataStorage::ObjectData elementData = MyDataStorage.CanvasData[i];

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
            MyDataStorage.CanvasData[i].selectionState = SelectionState::Empty;
        }
    } else {

    }
}

void AppFunctions::AddPoint(POINT point) {
    DataStorage::ObjectData elementData = {
        MyDataStorage.CanvasData.size(),
        "POINT",
        SelectionState::Hovering,
        point
    };

    MyDataStorage.CanvasData.push_back(elementData);
}

void AppFunctions::UpdatePoints(HDC hDeviceContext, int objectId) {
    int objectIdArraySize;
    int* objectIdArray;

    if (objectId == -1) {
        // Update all objects within the canvas by creating an array from all 
        // storage entries and passing it to DrawCanvasBitmap-Function.
        objectIdArraySize = MyDataStorage.CanvasData.size();
        objectIdArray = new int[objectIdArraySize];

        for (int i = 0; i < objectIdArraySize; i++) {
            objectIdArray[i] = MyDataStorage.CanvasData[i].id;
        }

        DrawCanvasBitmap(hDeviceContext, objectIdArray, objectIdArraySize);
    } else {
        // Update just a single object within the canvas by creating an array 
        // from a specified storage entry and passing it to DrawCanvasBitmap-
        // Function.
        objectIdArraySize = 1;
        objectIdArray = new int[objectIdArraySize];

        objectIdArray[0] = MyDataStorage.CanvasData[objectId].id;

        DrawCanvasBitmap(hDeviceContext, objectIdArray, objectIdArraySize);
    }

    delete[] objectIdArray;
}

SelectionState AppFunctions::GetSelectionState(int elementId) {

    return MyDataStorage.CanvasData[elementId].selectionState;
}

POINT AppFunctions::UpdateSelectionState(int elementId, SelectionState selectionState) {
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
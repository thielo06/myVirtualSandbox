#ifndef APP_FUNCTIONS_H
#define APP_FUNCTIONS_H

#include "Header.h"

namespace AppFunctions
{
    class DataStorage;

    int DrawBitmap(INT bitmapId, HDC hDeviceContext, LONG bitmapX, LONG bitmapY, LPWSTR bitmapOrigin);

    int GetSelectionState(int pointId);

    int SearchPoint(INT32 xValue, INT32 yValue);

    void ResetSelection();

    void AddPoint(POINT point);

    void UpdatePoints(HDC hDeviceContext, int pointId=-1);

    POINT UpdateSelectionState(int pointId, int selectionState);

    void TextOutput(HWND hOutputWnd, LPWSTR tempTextBuffer);
};

class AppFunctions::DataStorage {
public:
    struct ElementData {
        int id;
        string type;
        int selectionState;
        POINT position;
    };

    vector<ElementData> CanvasData;

    DataStorage();
};

extern AppFunctions::DataStorage MyDataStorage;

#endif APP_FUNCTIONS_H
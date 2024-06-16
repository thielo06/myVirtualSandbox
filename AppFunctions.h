#ifndef APP_FUNCTIONS_H
#define APP_FUNCTIONS_H

#include "Header.h"

namespace AppFunctions {
    // Forward declaration the class for data storage and subsequent definition.
    class DataStorage;

    enum class Alignment {
        North,
        NorthEast,
        East,
        SouthEast,
        South,
        SouthWest,
        West,
        NorthWest,
        Center
    };

    int DrawBitmap(
        HDC hDeviceContext,
        INT bitmapId,
        LONG bitmapX,
        LONG bitmapY,
        Alignment bitmapOrigin = AppFunctions::Alignment::Center
    );

    int DrawCanvasBitmap(
        HDC hDeviceContext,
        int* objectIdArray,
        int objectIdArraySize,
        Alignment bitmapOrigin = AppFunctions::Alignment::Center
    );

    SelectionState GetSelectionState(int pointId);

    int SearchDataStorage(POINT point);

    void ResetSelection();

    void AddPoint(POINT point);

    void UpdatePoints(HDC hDeviceContext, int pointId=-1);

    POINT UpdateSelectionState(int pointId, SelectionState selectionState);

    void TextOutput(HWND hOutputWnd, LPWSTR tempTextBuffer);
};

class AppFunctions::DataStorage {
public:
    struct ObjectData {
        int id;
        string type;
        SelectionState selectionState;
        POINT position;
    };

    vector<ObjectData> CanvasData;

    DataStorage();
};

extern AppFunctions::DataStorage MyDataStorage;

#endif APP_FUNCTIONS_H
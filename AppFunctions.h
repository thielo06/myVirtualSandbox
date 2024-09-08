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

    int DrawCanvasObject(
        HDC hDeviceContext,
        int* objectIdArray,
        int objectIdArraySize,
        Alignment bitmapOrigin = AppFunctions::Alignment::Center
    );

    SelectionState GetSelectionState(int pointId);

    /**
     * @brief Search for the given point object within the data storage.
     *
     * @param point is the object that is searched for.
     * @return Object identifier as an integer if point was found, -1 if not.
     */
    int SearchDataStorage(POINT point);

    void ResetSelection();

    void AddPoint(POINT point);

    /**
     * @brief Call the drawing function for an object if identifier is 
     * specified, if the identifier is not specified or -1 all objects 
     * are updated.
     *
     * @param hDeviceContext is the handle of the canvas to be drawn on.
     * @param pointId is the identifier of the object to be updated.
     */
    void UpdateObjects(HDC hDeviceContext, int pointId=-1);

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

    vector<ObjectData> CanvasObjects;

    DataStorage();
};

extern AppFunctions::DataStorage MyDataStorage;

#endif APP_FUNCTIONS_H
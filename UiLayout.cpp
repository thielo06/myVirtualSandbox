#include "UiLayout.h"

ColorPalette::ColorPalette() {
    TextColorDarkTheme = RGB(248, 248, 248);

    BackgroundColorDarkTheme = RGB(65, 65, 65);

    ElevatedColorDarkTheme = RGB(49, 49, 49);

    FrameColorDarkTheme = RGB(82, 82, 82);

    RedAccentDarkTheme = RGB(202, 62, 71);

    BlueAccentDarkTheme = RGB(12, 85, 190);

    YellowAccentDarkTheme = RGB(255, 201, 14);
}

// Initialization of the user interface objects that are declared in 
// "UiLayout"-Header. After each assignment the address of the object 
// is stored in the "Objects"-Vector. 
UiObjects::UiObjects() {
    Canvas = {
        L"myVirtualSandbox Canvas Class",
        L"Canvas",
        WS_VISIBLE | WS_CHILD,
        CANVAS_HOR_OFFSET,
        CANVAS_VER_OFFSET,
        CANVAS_WIDTH,
        CANVAS_HEIGHT,
        (HMENU)CanvasId,
        NULL,
        MyColors.ElevatedColorDarkTheme
    };
    pObjects.push_back(&Canvas);

    Output = {
        L"EDIT",
        NULL,
        // Add "ES_READONLY" to make it unaccessible for the user. 
        // Take note that you have to handle "WM_CTLCOLORSTATIC" 
        // message then.
        WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_VSCROLL,
        CANVAS_HOR_OFFSET,
        CANVAS_VER_OFFSET + CANVAS_HEIGHT + OUTPUT_VER_OFFSET,
        CANVAS_WIDTH,
        OUTPUT_HEIGHT,
        (HMENU)OutputId,
        NULL,
        MyColors.ElevatedColorDarkTheme
    };
    pObjects.push_back(&Output);

    AddPointButton = {
        L"BUTTON",
        L"Add Button",
        // With the 'BS_OWNERDRAW'-Option the owner 
        // window receives a 'WM_DRAWITEM'-Message when
        // a visual aspect of the button has changed.
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH,
        CANVAS_VER_OFFSET,
        SYMBOL_BUTTON_WIDTH,
        SYMBOL_BUTTON_HEIGHT,
        (HMENU)AddPointButtonId,
        NULL,
        MyColors.ElevatedColorDarkTheme
    };
    pObjects.push_back(&AddPointButton);

    HorCoordinateTextBox = {
        L"EDIT",
        NULL,
        WS_VISIBLE | WS_CHILD | ES_RIGHT,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + SYMBOL_BUTTON_WIDTH + ENTRY_VER_OFFSET,
        CANVAS_VER_OFFSET,
        ENTRY_WIDTH,
        ENTRY_HEIGHT,
        (HMENU)HorCoordinateTextBoxId,
        NULL,
        MyColors.ElevatedColorDarkTheme
    };
    pObjects.push_back(&HorCoordinateTextBox);

    VerCoordinateTextBox = {
        L"EDIT",
        NULL,
        WS_VISIBLE | WS_CHILD | ES_RIGHT,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + SYMBOL_BUTTON_WIDTH + ENTRY_VER_OFFSET + ENTRY_WIDTH + ENTRY_VER_OFFSET,
        CANVAS_VER_OFFSET,
        ENTRY_WIDTH,
        ENTRY_HEIGHT,
        (HMENU)VerCoordinateTextBoxId,
        NULL,
        MyColors.ElevatedColorDarkTheme

    };
    pObjects.push_back(&VerCoordinateTextBox);

    CloseApplicationButton = {
        L"BUTTON",
        L"Close",
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        CANVAS_HOR_OFFSET,
        CANVAS_VER_OFFSET + CANVAS_HEIGHT + OUTPUT_VER_OFFSET + OUTPUT_HEIGHT + SYMBOL_BUTTON_HEIGHT + BUTTON_VER_OFFSET,
        BUTTON_WIDTH,
        BUTTON_HEIGHT,
        (HMENU)CloseApplicationButtonId,
        NULL,
        MyColors.ElevatedColorDarkTheme
    };
    pObjects.push_back(&CloseApplicationButton);

    ResetOutputButton = {
        L"BUTTON",
        L"Reset Output",
        WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
        CANVAS_HOR_OFFSET,
        CANVAS_VER_OFFSET + CANVAS_HEIGHT + OUTPUT_VER_OFFSET + OUTPUT_HEIGHT,
        SYMBOL_BUTTON_WIDTH,
        SYMBOL_BUTTON_HEIGHT,
        (HMENU)ResetOutputButtonId,
        NULL,
        MyColors.ElevatedColorDarkTheme
    };
    pObjects.push_back(&ResetOutputButton);
}
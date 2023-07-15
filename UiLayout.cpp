#include "Header.h"
#include "UiLayout.h"

ColorPalette::ColorPalette() {
    TextColorDarkTheme = RGB(248, 248, 248);

    BackgroundColorDarkTheme = RGB(65, 65, 65);

    ElevatedColorDarkTheme = RGB(49, 49, 49);

    FrameColorDarkTheme = RGB(82, 82, 82);

    AccentColorDarkTheme = RGB(202, 62, 71);
}

// Initialization of the user interface objects that are declared in 
// "UiLayout"-Header. After each assignment the address of the object 
// is stored in the "Objects"-Vector. 
UiObjects::UiObjects() {
    Canvas = {
        L"myVirtualSandbox Canvas Class",
        L"Canvas",
        WS_VISIBLE | WS_CHILD | WS_BORDER,
        CANVAS_HOR_OFFSET,
        CANVAS_VER_OFFSET,
        CANVAS_WIDTH,
        CANVAS_HEIGTH,
        NULL,
        NULL,
        ObjectClass::Custom,
        MyColors.ElevatedColorDarkTheme
    };
    Objects.push_back(&Canvas);

    Output = {
        L"EDIT",
        L"Output",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE, // Add ES_READONLY to make it unaccessible for the user.
        CANVAS_HOR_OFFSET,
        CANVAS_VER_OFFSET + CANVAS_HEIGTH + OUTPUT_VER_OFFSET,
        CANVAS_WIDTH,
        OUTPUT_HEIGTH,
        (HMENU)200,
        NULL,
        ObjectClass::Custom,
        MyColors.ElevatedColorDarkTheme
    };
    Objects.push_back(&Output);

    Button1 = {
        L"BUTTON",
        L"Button1",
        // With the 'BS_OWNERDRAW'-Option the owner 
        // window receives a 'WM_DRAWITEM'-Message when
        // a visual aspect of the button has changed.
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + BUTTON_HOR_OFFSET,
        CANVAS_VER_OFFSET,
        BUTTON_WIDTH,
        BUTTON_HEIGTH,
        (HMENU)100,
        NULL,
        ObjectClass::Button,
        MyColors.ElevatedColorDarkTheme
    };
    Objects.push_back(&Button1);

    Button2 = {
        L"BUTTON",
        L"Close",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + BUTTON_HOR_OFFSET + BUTTON_WIDTH + BUTTON_HOR_OFFSET,
        CANVAS_VER_OFFSET,
        BUTTON_WIDTH,
        BUTTON_HEIGTH,
        (HMENU)101,
        NULL,
        ObjectClass::Button,
        MyColors.ElevatedColorDarkTheme
    };

    Objects.push_back(&Button2);
}
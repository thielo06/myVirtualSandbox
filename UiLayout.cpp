#include "Header.h"
#include "UiLayout.h"

ColorPalette::ColorPalette() {
    TextColorDarkTheme = RGB(248, 248, 248);

    BackgroundColorDarkTheme = RGB(65, 65, 65);

    ElevatedColorDarkTheme = RGB(49, 49, 49);

    FrameColorDarkTheme = RGB(82, 82, 82);

    AccentColorDarkTheme = RGB(202, 62, 71);
}

UiObjects::UiObjects() {
    #pragma region Canvas
    Canvas.classIdentifier = L"myVirtualSandbox Canvas Class";
    Canvas.color = MyColors.ElevatedColorDarkTheme;
    Canvas.objectTitle = L"Canvas";
    Canvas.objectType = ObjectType::Custom;
    Canvas.objectStyles = WS_VISIBLE | WS_CHILD | WS_BORDER;
    Canvas.rectangle = {
        CANVAS_HOR_OFFSET,
        CANVAS_VER_OFFSET,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH,
        CANVAS_VER_OFFSET + CANVAS_HEIGTH
    };

    Objects.push_back(Canvas);
    #pragma endregion

    #pragma region Output
    Output.classIdentifier = L"EDIT";
    Output.color = MyColors.ElevatedColorDarkTheme;
    Output.objectTitle = L"Output";
    Output.objectType = ObjectType::Custom;
    Output.objectStyles = WS_VISIBLE | WS_CHILD | WS_BORDER;
    Output.rectangle = {
        CANVAS_HOR_OFFSET,
        CANVAS_VER_OFFSET + CANVAS_HEIGTH + OUTPUT_VER_OFFSET,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH,
        CANVAS_VER_OFFSET + CANVAS_HEIGTH + OUTPUT_VER_OFFSET + OUTPUT_HEIGTH
    };

    Objects.push_back(Output);
    #pragma endregion

    #pragma region Button1
    Button1.classIdentifier = L"BUTTON";
    Button1.color = MyColors.ElevatedColorDarkTheme;
    Button1.objectTitle = L"Button1";
    Button1.objectType = ObjectType::Button;
    // With the 'BS_OWNERDRAW'-Option the owner 
    // window receives a 'WM_DRAWITEM'-Message when
    // a visual aspect of the button has changed.
    Button1.objectStyles = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW;
    Button1.rectangle = {
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + BUTTON_HOR_OFFSET,
        CANVAS_VER_OFFSET,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + BUTTON_HOR_OFFSET + BUTTON_WIDTH,
        CANVAS_VER_OFFSET + BUTTON_HEIGTH
    };

    Button1.controlIdentifier = (HMENU)100;

    Objects.push_back(Button1);
    #pragma endregion

    #pragma region Button2
    Button2.classIdentifier = L"BUTTON";
    Button2.color = MyColors.ElevatedColorDarkTheme;
    Button2.objectTitle = L"Close";
    Button2.objectType = ObjectType::Button;
    Button2.objectStyles = WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW;
    Button2.rectangle = {
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + BUTTON_HOR_OFFSET + BUTTON_WIDTH + BUTTON_HOR_OFFSET,
        CANVAS_VER_OFFSET,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + BUTTON_HOR_OFFSET + BUTTON_WIDTH + BUTTON_HOR_OFFSET + BUTTON_WIDTH,
        CANVAS_VER_OFFSET + BUTTON_HEIGTH
    };

    Button2.controlIdentifier = (HMENU)101;

    Objects.push_back(Button2);
    #pragma endregion
}
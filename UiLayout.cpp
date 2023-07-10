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
    Canvas.color = MyColors.ElevatedColorDarkTheme;
    Canvas.objectText = L"Canvas1";
    Canvas.objectType = 0;
    Canvas.rectangle = {
        CANVAS_HOR_OFFSET,
        CANVAS_VER_OFFSET,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH,
        CANVAS_VER_OFFSET + CANVAS_HEIGTH
    };

    Objects.push_back(Canvas);
    #pragma endregion

    #pragma region Button1
    Button1.color = MyColors.ElevatedColorDarkTheme;
    Button1.identifier = 100;
    Button1.objectText = L"Button1";
    Button1.objectType = 1;
    Button1.rectangle = {
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10,
        CANVAS_VER_OFFSET,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10 + BUTTON_WIDTH,
        CANVAS_VER_OFFSET + BUTTON_HEIGTH
    };

    Objects.push_back(Button1);
    #pragma endregion

    #pragma region Button2
    Button2.color = MyColors.ElevatedColorDarkTheme;
    Button2.identifier = 101;
    Button2.objectText = L"Close";
    Button2.objectType = 1;
    Button2.rectangle = {
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10,
        CANVAS_VER_OFFSET + CANVAS_HEIGTH - BUTTON_HEIGTH,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10 + BUTTON_WIDTH,
        CANVAS_VER_OFFSET + CANVAS_HEIGTH
    };

    Objects.push_back(Button2);
    #pragma endregion
}
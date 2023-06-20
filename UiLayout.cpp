#include "Header.h"
#include "UiLayout.h"

ColorPalette::ColorPalette() {
    BackgroundColorDarkTheme = RGB(65, 65, 65);

    ElevatedColorDarkTheme = RGB(49, 49, 49);

    FrameColorDarkTheme = RGB(82, 82, 82);

    AccentColorDarkTheme = RGB(202, 62, 71);
}

Forms::Forms() {
    Canvas.rectangle = {
        CANVAS_HOR_OFFSET,
        CANVAS_VER_OFFSET,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH,
        CANVAS_VER_OFFSET + CANVAS_HEIGHT
    };
    Canvas.color = MyColors.ElevatedColorDarkTheme;
    allRectangles[0] = Canvas;

    Button1.rectangle = {
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10,
        CANVAS_VER_OFFSET,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10 + BUTTON_1_WIDTH,
        CANVAS_VER_OFFSET + BUTTON_1_HEIGTH
    };
    Button1.color = MyColors.ElevatedColorDarkTheme;
    allRectangles[1] = Button1;

    Button2.rectangle = {
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10,
        CANVAS_VER_OFFSET + BUTTON_1_HEIGTH + 10,
        CANVAS_HOR_OFFSET + CANVAS_WIDTH + 10 + BUTTON_1_WIDTH,
        CANVAS_VER_OFFSET + BUTTON_1_HEIGTH + 10 + BUTTON_1_HEIGTH
    };
    Button2.color = MyColors.ElevatedColorDarkTheme;
    allRectangles[2] = Button2;
}
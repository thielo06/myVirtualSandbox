#include "AppFunctions.h"
#include "Header.h"
#include "UiLayout.h"

LRESULT CALLBACK wndProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);

int __stdcall wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
) {
    // A window class defines a set of behaviors that several windows 
    // might have in common. Every window must be associated with a 
    // window class. To register a window class, fill in a "WNDCLASS" 
    // structure and call "RegisterClass" function afterwards.
    const wchar_t CLASS_NAME[] = L"myVirtualSandbox Window Class";

    BOOL useDarkMode;
    HWND hWnd;
    MSG msg = { };
    WNDCLASS wndClass = { };

    wndClass.lpfnWndProc = wndProc;
    wndClass.hInstance = hInstance;
    wndClass.lpszClassName = CLASS_NAME;

    RegisterClass(&wndClass);

    // Create the window.
    hWnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hWnd == NULL)
    {
        return 0;
    }

    #ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
    #define DWMWA_USE_IMMERSIVE_DARK_MODE 20
    #endif

    useDarkMode = TRUE;

    DwmSetWindowAttribute(
        hWnd,
        DWMWA_USE_IMMERSIVE_DARK_MODE,
        &useDarkMode,
        sizeof(useDarkMode)
    );

    ShowWindow(hWnd, nShowCmd);

    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK wndProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (uMsg)
    {
        case WM_CREATE:
        {
            // The following loop iterates through the container of user 
            // interface objects and if the object is of button type then
            // it is added to the user interface.
            for (int i = 0; i < MyUiObjects.Objects.size(); i++) {
                UiObjects::Object UiObject = MyUiObjects.Objects[i];

                switch (UiObject.objectType) {
                case 1: // Button
                {
                    HBRUSH hBrush;
                    HWND hButtonWnd;
                    
                    hBrush = CreateSolidBrush(UiObject.color);

                    hButtonWnd = CreateWindowEx(
                        0,
                        L"BUTTON", // Predefined class; Unicode assumed 
                        UiObject.objectText, // Button text 
                        // With the 'BS_OWNERDRAW'-Option the owner 
                        // window receives a 'WM_DRAWITEM'-Message when
                        // a visual aspect of the button has changed.
                        WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | BS_OWNERDRAW, // Styles 
                        UiObject.rectangle.left, // x position 
                        UiObject.rectangle.top, // y position 
                        BUTTON_WIDTH, // Button width
                        BUTTON_HEIGTH, // Button height
                        hWnd, // Parent window
                        NULL, // No menu.
                        (HINSTANCE)GetModuleHandle(NULL),
                        NULL // Pointer not needed.
                    );

                    DeleteObject(hBrush);
                }
                }
            }
            return 0;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);

            return 0;
        }

        case WM_DRAWITEM:
        {
            HBRUSH hElevatedColorBrush, hFrameColorBrush;
            HDC hDeviceContext;
            HFONT hItemFont, hOldItemFont;
            HWND hItemWnd;
            int itemState;
            LPDRAWITEMSTRUCT itemStructure;
            LPWSTR lpBuffer;
            RECT itemRectangle;

            // The 'lparam'-Parameter of 'WM_DRAWITEM'-Message holds
            // a pointer to a 'DRAWITEMSTRUCT'-Structure wich provides
            // informations to the owner window on how to paint the 
            // control or menu-item.
            itemStructure = (LPDRAWITEMSTRUCT)lParam;

            hDeviceContext = itemStructure->hDC;
            hItemWnd = itemStructure->hwndItem;
            itemRectangle = itemStructure->rcItem;
            itemState = itemStructure->itemState;

            hElevatedColorBrush = CreateSolidBrush(MyColors.ElevatedColorDarkTheme);
            hFrameColorBrush = CreateSolidBrush(MyColors.FrameColorDarkTheme);

            if (itemState & ODS_SELECTED) {
                FillRect(
                    hDeviceContext,
                    &itemRectangle,
                    hFrameColorBrush
                );
            }
            else {
                FillRect(
                    hDeviceContext,
                    &itemRectangle,
                    hElevatedColorBrush
                );
            }

            int length;
            length = GetWindowTextLength(hItemWnd);

            lpBuffer = new wchar_t[length + 1];
            GetWindowText(hItemWnd, lpBuffer, length + 1);

            hItemFont = CreateFont(
                15,
                0,
                0, 
                0, 
                FW_DONTCARE,
                false, // bItalic
                false, // bUnderline
                false, // bStrikeOut
                DEFAULT_CHARSET,
                OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DRAFT_QUALITY, VARIABLE_PITCH,
                L"Arial"
            );

            hOldItemFont = (HFONT)SelectObject(hDeviceContext, hItemFont);

            SetTextColor(hDeviceContext, MyColors.TextColorDarkTheme);
            SetBkMode(hDeviceContext, TRANSPARENT);
            DrawText(
                hDeviceContext,
                lpBuffer,
                length,
                &itemRectangle,
                DT_CENTER | DT_VCENTER | DT_SINGLELINE
            );

            SelectObject(hDeviceContext, hOldItemFont);
            DeleteObject(hItemFont);

            DeleteObject(hElevatedColorBrush);
            DeleteObject(hFrameColorBrush);

            return 0;
        }

        // To paint the window the "WM_PAINT" message has to be 
        // received by the window. It is sent by either the program 
        // itself or the operating system.
        case WM_PAINT:
        {
            // The "rcPaint" member of the "PAINTSTRCUT" structure 
            // returns a "RECT" structure that specifies the upper 
            // left and lower right corners of the rectangle in wich 
            // the painting is requested.
            PAINTSTRUCT paintStruct;
            HDC hDeviceContext;

            HBRUSH hBackgroundColorBrush, hElevatedColorBrush, hFrameColorBrush;
            
            hDeviceContext = BeginPaint(hWnd, &paintStruct);
            
            hBackgroundColorBrush = CreateSolidBrush(MyColors.BackgroundColorDarkTheme);
            hElevatedColorBrush = CreateSolidBrush(MyColors.ElevatedColorDarkTheme);
            hFrameColorBrush = CreateSolidBrush(MyColors.FrameColorDarkTheme);

            FillRect(
                hDeviceContext,
                &paintStruct.rcPaint,
                hBackgroundColorBrush
            );
                
            FillRect(
                hDeviceContext,
                &MyUiObjects.Canvas.rectangle,
                hElevatedColorBrush
            );
            AppFunctions::FrameRectangle(
                hDeviceContext,
                MyUiObjects.Canvas.rectangle,
                hFrameColorBrush
            );

            DeleteObject(hBackgroundColorBrush);
            DeleteObject(hElevatedColorBrush);
            DeleteObject(hFrameColorBrush);

            EndPaint(hWnd, &paintStruct);

            return 0;
        }

        // When the mouse moves over a window, the window receives a 
        // "WM_SETCURSOR" message.
        case WM_SETCURSOR:
        {
            HCURSOR cursor;
            LPWSTR value;

            switch (LOWORD(lParam)) {
                case HTBOTTOM: {
                    value = IDC_SIZENS;
                    break;
                }
                case HTBOTTOMLEFT: {
                    value = IDC_SIZENESW;
                    break;
                }
                case HTBOTTOMRIGHT: {
                    value = IDC_SIZENWSE;
                    break;
                }
                case HTLEFT: {
                    value = IDC_SIZEWE;
                    break;
                }
                case HTRIGHT: {
                    value = IDC_SIZEWE;
                    break;
                }
                case HTTOP: {
                    value = IDC_SIZENS;
                    break;
                }
                case HTTOPLEFT: {
                    value = IDC_SIZENWSE;
                    break;
                }
                case HTTOPRIGHT: {
                    value = IDC_SIZENESW;
                    break;
                }
                default: value = IDC_ARROW;
            }

            cursor = LoadCursor(NULL, value);

            SetCursor(cursor);

            return 0;
        }

        case WM_LBUTTONDOWN:
        {
            POINT pt;

            pt.x = GET_X_LPARAM(lParam);
            pt.y = GET_Y_LPARAM(lParam);

            // In case that the mouse is within the canvas area, the 
            // "DrawPoint" function is called.
            if (AppFunctions::Contains(MyUiObjects.Canvas.rectangle, pt)) {
                AppFunctions::DrawPoint(hWnd, pt, MyColors.AccentColorDarkTheme);
            }

            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
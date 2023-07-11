#include "AppFunctions.h"
#include "Header.h"
#include "UiLayout.h"

LRESULT CALLBACK wndProc(
    HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);

LRESULT CALLBACK canvasWndProc(
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
    const wchar_t CLASS_NAME[] = L"myVirtualSandbox Window Class";

    BOOL useDarkMode;
    HWND hApplicationWnd;
    MSG msg = { };
    // A window class defines a set of behaviors that several windows 
    // might have in common. Every window must be associated with a 
    // window class. To register a window class, fill in a "WNDCLASS" 
    // structure and call "RegisterClass" function afterwards.
    WNDCLASS applicationWndClass = { };

    applicationWndClass.lpfnWndProc = wndProc;
    applicationWndClass.hInstance = hInstance;
    applicationWndClass.lpszClassName = CLASS_NAME;

    RegisterClass(&applicationWndClass);

    // Create the window.
    hApplicationWnd = CreateWindow(
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

    if (hApplicationWnd == NULL)
    {
        return 0;
    }

    #ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
    #define DWMWA_USE_IMMERSIVE_DARK_MODE 20
    #endif

    useDarkMode = TRUE;

    DwmSetWindowAttribute(
        hApplicationWnd,
        DWMWA_USE_IMMERSIVE_DARK_MODE,
        &useDarkMode,
        sizeof(useDarkMode)
    );

    ShowWindow(hApplicationWnd, nShowCmd);

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
        // The following message is sent among others when a control 
        // like a button sends a notification message to its parent 
        // window.
        // In case this message is actually sent by a control, its low-
        // order word of the word parameter stores the control identifier
        // wich is set on object initialization with the "hMenu"-
        // Parameter.
        case WM_COMMAND:
        {
            DWORD controlIdentifier;

            controlIdentifier = LOWORD(wParam);

            switch (controlIdentifier) {
                case 100:
                {
                    System::Diagnostics::Debug::WriteLine("Button1");

                    break;
                }
                case 101:
                {
                    System::Diagnostics::Debug::WriteLine("Close Window ...");

                    SendMessage(hWnd, WM_DESTROY, NULL, NULL);

                    break;
                }
            }
            break;
        }
        case WM_CREATE:
        {
            HINSTANCE hInstance;
            WNDCLASS canvasWndClass;

            hInstance = (HINSTANCE)GetModuleHandle(NULL);

            canvasWndClass = { };

            canvasWndClass.lpfnWndProc = canvasWndProc;
            canvasWndClass.hInstance = hInstance;
            canvasWndClass.lpszClassName = L"myVirtualSandbox Canvas Class";

            RegisterClass(&canvasWndClass);

            // The following loop iterates through the container of user 
            // interface objects and if the object is of button type then
            // it is added to the user interface.
            for (int i = 0; i < MyUiObjects.Objects.size(); i++) {
                UiObjects::Object UiObject = MyUiObjects.Objects[i];

                HWND hUiObjectWnd;

                // Create the window.
                hUiObjectWnd = CreateWindow(
                    UiObject.classIdentifier, // Window class
                    UiObject.objectTitle,    // Window text
                    UiObject.objectStyles, // Styles 
                    UiObject.rectangle.left, // Horizontal position 
                    UiObject.rectangle.top, // Vertical position 
                    UiObject.rectangle.right - UiObject.rectangle.left, // Width
                    UiObject.rectangle.bottom - UiObject.rectangle.top, // Height
                    hWnd, // Parent window
                    UiObject.controlIdentifier, // No menu.
                    hInstance,
                    NULL // Pointer not needed.
                );
            }
            break;
        }
        case WM_DESTROY:
        {
            PostQuitMessage(0);

            break;
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
                L"Calibri"
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

            break;
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

            HBRUSH hBrush;
            
            hDeviceContext = BeginPaint(hWnd, &paintStruct);
            hBrush = CreateSolidBrush(MyColors.BackgroundColorDarkTheme);

            // Paint application background.
            FillRect(
                hDeviceContext,
                &paintStruct.rcPaint,
                hBrush
            );

            DeleteObject(hBrush);

            EndPaint(hWnd, &paintStruct);

            break;
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

            break;
        }

        case WM_LBUTTONDOWN:
        {

            break;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK canvasWndProc(
    HWND hCanvasWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (uMsg)
    {
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

            HBRUSH hBrush;

            hDeviceContext = BeginPaint(hCanvasWnd, &paintStruct);
            hBrush = CreateSolidBrush(MyColors.ElevatedColorDarkTheme);

            // Paint application background.
            FillRect(
                hDeviceContext,
                &paintStruct.rcPaint,
                hBrush
            );

            DeleteObject(hBrush);

            EndPaint(hCanvasWnd, &paintStruct);

            break;
        }

        case WM_LBUTTONDOWN:
        {
            POINT point;

            point.x = GET_X_LPARAM(lParam);
            point.y = GET_Y_LPARAM(lParam);

            AppFunctions::DrawPoint(hCanvasWnd, point, MyColors.AccentColorDarkTheme);
            
            break;
        }
    }

    return DefWindowProc(hCanvasWnd, uMsg, wParam, lParam);
}
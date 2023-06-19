#include "Header.h"

#include "ColorPalette.h"
#include "Forms.h"

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
        case WM_DESTROY:
        {
            PostQuitMessage(0);

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
            
            for (int i = 0; i < MyForms.arraySize; i++) {
                Forms::rectangle rectangle;
                HBRUSH hBrush;

                rectangle = MyForms.allRectangles[i];
                hBrush = CreateSolidBrush(rectangle.color);
                
                FillRect(
                    hDeviceContext,
                    &rectangle.rectangle,
                    hElevatedColorBrush
                );
                FrameRectangle(
                    hDeviceContext,
                    rectangle.rectangle,
                    hFrameColorBrush
                );
            }

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
            if (Contains(MyForms.Canvas.rectangle, pt)) {
                DrawPoint(hWnd, pt, MyColors.AccentColorDarkTheme);
            }

            return 0;
        }
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
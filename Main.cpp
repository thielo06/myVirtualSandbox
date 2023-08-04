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
        // Its low-order word of the word parameter stores the control 
        // identifier wich is set on object initialization with the 
        // "hMenu"-Parameter.
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
                case 102:
                {
                    HWND hOutputWnd;
                    
                    hOutputWnd = MyObjects.Output.hObjectWnd;

                    SendMessage(hOutputWnd, WM_SETTEXT, NULL, NULL);

                    break;
                }
            }
            break;
        }

        case WM_CREATE:
        {
            HANDLE hImage;
            HFONT hFont;
            HINSTANCE hInstance;
            WNDCLASS canvasWndClass;

            // Create a font object that is used for all windows from 
            // the default font of user interface objects.
            hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

            hInstance = (HINSTANCE)GetModuleHandle(NULL);

            canvasWndClass = { };

            canvasWndClass.lpfnWndProc = canvasWndProc;
            canvasWndClass.hInstance = hInstance;
            canvasWndClass.lpszClassName = L"myVirtualSandbox Canvas Class";

            RegisterClass(&canvasWndClass);

            AppFunctions::InitializeXmlDocument();

            // The following loop iterates through the container of user 
            // interface objects.
            for (int i = 0; i < (int)MyObjects.Objects.size(); i++) {
                UiObjects::Object* pObject = MyObjects.Objects[i];
                
                HWND hObjectWnd;
                
                hObjectWnd = CreateWindow(
                    pObject->lpClassName, // Window class
                    pObject->lpWindowName,    // Window text
                    pObject->dwStyle, // Styles 
                    pObject->x, // Horizontal position 
                    pObject->y, // Vertical position 
                    pObject->nWidth, // Width
                    pObject->nHeigth, // Height
                    hWnd, // Parent window
                    pObject->hMenu, // No menu.
                    hInstance,
                    NULL // Pointer not needed.
                );

                // Send 'WM_SETFONT' message to each window to set the 
                // font to default font for user interface objects. 
                SendMessage(hObjectWnd, WM_SETFONT, (WPARAM)hFont, TRUE);

                pObject->hObjectWnd = hObjectWnd;
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
            HDC hDeviceContext;
            HWND hItemWnd;
            LPDRAWITEMSTRUCT itemStructure;
            RECT itemRectangle;

            int itemState, length, controlIdentifier;

            controlIdentifier = (int)wParam;

            // The 'lparam'-Parameter of 'WM_DRAWITEM'-Message holds
            // a pointer to a 'DRAWITEMSTRUCT'-Structure wich provides
            // informations to the owner window on how to paint the 
            // control or menu-item.
            itemStructure = (LPDRAWITEMSTRUCT)lParam;

            hDeviceContext = itemStructure->hDC;
            hItemWnd = itemStructure->hwndItem;
            itemRectangle = itemStructure->rcItem;
            itemState = itemStructure->itemState;

            switch (controlIdentifier) {
                case 100:
                {
                    // Following the fallthrough behaviour of C++, the 
                    // code that applies to the lower case also 
                    // applies when this case is called.
                    // Note that the "break" statement is missing in 
                    // this case.
                }
                case 101:
                {
                    HBRUSH hBrush;
                    LPWSTR lpBuffer;

                    if (itemState & ODS_SELECTED) {
                        hBrush = CreateSolidBrush(MyColors.FrameColorDarkTheme);
                    }
                    else {
                        hBrush = CreateSolidBrush(MyColors.ElevatedColorDarkTheme);
                    }

                    FillRect(
                        hDeviceContext,
                        &itemRectangle,
                        hBrush
                    );

                    DeleteObject(hBrush);

                    // Create a buffer with length of the window text wich is 
                    // defined on object initialization.
                    length = GetWindowTextLength(hItemWnd);
                    lpBuffer = new wchar_t[length + 1];

                    // Get the window text and write it to the buffer.
                    GetWindowText(hItemWnd, lpBuffer, length + 1);

                    SetTextColor(hDeviceContext, MyColors.TextColorDarkTheme);
                    SetBkMode(hDeviceContext, TRANSPARENT);

                    // Draw text to the button.
                    DrawText(
                        hDeviceContext,
                        lpBuffer,
                        length,
                        &itemRectangle,
                        DT_CENTER | DT_VCENTER | DT_SINGLELINE
                    );

                    break;
                }
                case 102:
                {
                    BITMAP bitmap;
                    HBITMAP hBitmap;
                    HDC hdcMemDC;
                    HGDIOBJ oldBitmap;
                    HRSRC hImageResource;
                    LPWSTR bitmapResource;

                    // Create a compatible device context in reference 
                    // to the device context of item structure.
                    hdcMemDC = CreateCompatibleDC(hDeviceContext);

                    if (itemState & ODS_SELECTED) {
                        bitmapResource = MAKEINTRESOURCE(IDB_BITMAP2);
                    } else {
                        bitmapResource = MAKEINTRESOURCE(IDB_BITMAP1);
                    }

                    // Create a handle from the bitmap resource.
                    hBitmap = (HBITMAP)LoadImageW(
                        GetModuleHandle(NULL),
                        bitmapResource,
                        IMAGE_BITMAP,
                        0, 0,
                        NULL
                    );

                    // Select the bitmap handle to the source device 
                    // context and store a copy of it in a variable.
                    oldBitmap = SelectObject(hdcMemDC, hBitmap);

                    // Read graphical information from the handle 
                    // and write it to the buffer at specified 
                    // location.
                    GetObject(hBitmap, sizeof(bitmap), &bitmap);

                    // Perform a bit block transfer between the source 
                    // device context and the device context of the 
                    // item structure.
                    BitBlt(
                        hDeviceContext,
                        0, 0,
                        bitmap.bmWidth,
                        bitmap.bmHeight,
                        hdcMemDC,
                        0, 0,
                        SRCCOPY
                    );

                    // Select the original bitmap handle to the source 
                    // device context and delete the object.
                    SelectObject(hdcMemDC, oldBitmap);
                    DeleteDC(hdcMemDC);

                    break;
                }
            }

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

        case WM_CTLCOLOREDIT:
        {
            HBRUSH hBrush;
            HDC hEditControl;
            HFONT hItemFont;

            hEditControl = (HDC)wParam;

            SetTextColor(hEditControl, MyColors.TextColorDarkTheme);

            HWND hOutputWnd = MyObjects.Output.hObjectWnd;

            SetBkColor(hEditControl, MyColors.ElevatedColorDarkTheme);
            SetDCBrushColor(hEditControl, MyColors.ElevatedColorDarkTheme);

            return (HRESULT)GetStockObject(DC_BRUSH);
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
            HWND hOutputWnd;
            LPWSTR textOutput, wndTextBuffer;
            POINT point = {};

            int wndTextLength, textLength;

            point.x = GET_X_LPARAM(lParam);
            point.y = GET_Y_LPARAM(lParam);

            AppFunctions::DrawPoint(hCanvasWnd, point, MyColors.AccentColorDarkTheme);

            hOutputWnd = MyObjects.Output.hObjectWnd;

            // Check if hObjectWnd is a valid handle
            if (IsWindow(hOutputWnd))
            {
                // Create a buffer with length of the window text.
                wndTextLength = GetWindowTextLength(hOutputWnd) + 1;
                wndTextBuffer = new wchar_t[wndTextLength];

                // Get the window text and write it to the buffer.
                GetWindowText(hOutputWnd, wndTextBuffer, wndTextLength);

                wchar_t tempTextBuffer[256];

                wsprintfW(tempTextBuffer, L"%i, %i", point.x, point.y);

                // If the length of the window text is bigger than 
                // one, the window text is not empty and it is 
                // concatenated with the value of the temporary text 
                // buffer.
                // If it is equal to one it means that it is empty, so 
                // the text output is just the value of the tempory 
                // text buffer.
                if (wndTextLength > 1) {
                    // The length of the new text is the length of the 
                    // window text in addition to the tempory text 
                    // buffer.
                    // The array size is increased by three 
                    // characters, two for a linebreak "\r\n" and one 
                    // for the null terminator "\0".
                    textLength = wndTextLength + 2 + wcslen(tempTextBuffer) + 1;
                    textOutput = new wchar_t[textLength];

                    wsprintfW(textOutput, L"%s\r\n%s", wndTextBuffer, tempTextBuffer);
                } else {
                    textLength = wcslen(tempTextBuffer) + 1;
                    textOutput = new wchar_t[textLength];

                    wsprintfW(textOutput, L"%s", tempTextBuffer);
                }

                SendMessage(hOutputWnd, WM_SETTEXT, NULL, (LPARAM)textOutput);
            }
            else {

            }
            break;
        }
    }

    return DefWindowProc(hCanvasWnd, uMsg, wParam, lParam);
}
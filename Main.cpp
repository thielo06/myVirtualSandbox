#include "AppFunctions.h"
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
                case MyObjects.AddPointButtonId:
                {
                    CurrentToolState = ToolState::addPoint;

                    break;
                }
                case MyObjects.SelectPointButtonId:
                {
                    CurrentToolState = ToolState::selectPoint;

                    break;
                }
                case MyObjects.CloseApplicationButtonId:
                {
                    Debug::WriteLine("Close Window ...");

                    SendMessage(hWnd, WM_DESTROY, NULL, NULL);

                    break;
                }
                case MyObjects.ResetOutputButtonId:
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
                    pObject->hMenu, // Corresponding menu gained from objectControlId.
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
                case MyObjects.AddPointButtonId:
                {
                    // Following the fallthrough behaviour of C++, the 
                    // code that applies to the lower case also 
                    // applies when this case is called.
                    // Note that the "break" statement is missing in 
                    // this case.

                    if (itemState & ODS_SELECTED) {
                        AppFunctions::DrawBitmap(IDB_BITMAP5, hDeviceContext, 0, 0, L"nw");
                    }
                    else {
                        AppFunctions::DrawBitmap(IDB_BITMAP4, hDeviceContext, 0, 0, L"nw");
                    }

                    break;
                }
                case MyObjects.SelectPointButtonId:
                {
                    if (itemState & ODS_SELECTED) {
                        AppFunctions::DrawBitmap(IDB_BITMAP7, hDeviceContext, 0, 0, L"nw");
                    }
                    else {
                        AppFunctions::DrawBitmap(IDB_BITMAP6, hDeviceContext, 0, 0, L"nw");
                    }

                    break;
                }
                case MyObjects.CloseApplicationButtonId:
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
                case MyObjects.ResetOutputButtonId:
                {
                    if (itemState & ODS_SELECTED) {
                        AppFunctions::DrawBitmap(IDB_BITMAP2, hDeviceContext, 0, 0, L"nw");
                    } else {
                        AppFunctions::DrawBitmap(IDB_BITMAP1, hDeviceContext, 0, 0, L"nw");
                    }

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
            HDC hEditControl;

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
        case WM_CREATE:
        {
            ToolState currentToolState = ToolState::empty;

            break;
        }

        // To paint the window the "WM_PAINT" message has to be 
        // received by the window. It is sent by either the program 
        // itself or the operating system.
        case WM_PAINT:
        {
            HBRUSH hBrush;
            HDC hDeviceContext;

            // The "rcPaint" member of the "PAINTSTRCUT" structure 
            // returns a "RECT" structure that specifies the upper 
            // left and lower right corners of the rectangle in wich 
            // the painting is requested.
            PAINTSTRUCT paintStruct;

            hDeviceContext = BeginPaint(hCanvasWnd, &paintStruct);

            hBrush = CreateSolidBrush(MyColors.ElevatedColorDarkTheme);

            if (wParam == WM_LBUTTONDOWN || wParam == WM_MOUSEHOVER) {
                // Update a single object.
                AppFunctions::UpdatePoints(hDeviceContext, lParam);
            } else {
                // Update all objects.
                FillRect(
                    hDeviceContext,
                    &paintStruct.rcPaint,
                    hBrush
                );

                AppFunctions::UpdatePoints(hDeviceContext, -1);
            }

            DeleteObject(hBrush);

            EndPaint(hCanvasWnd, &paintStruct);

            break;
        }

        case WM_LBUTTONDOWN:
        {
            HWND hOutputWnd;
            LPWSTR textOutput, wndTextBuffer;

            int xValue, yValue, textLength, wndTextLength;

            xValue = GET_X_LPARAM(lParam);
            yValue = GET_Y_LPARAM(lParam);

            POINT currentPosition = {
                GET_X_LPARAM(lParam),
                GET_Y_LPARAM(lParam)
            };

            int pointId = AppFunctions::SearchDataStorage(currentPosition);

            // If current mouse position was not found in data storage ...
            if (pointId == -1) {
                switch (CurrentToolState) {
                    // ... add a point.
                    case ToolState::addPoint:
                    {
                        AppFunctions::AddPoint(currentPosition);

                        InvalidateRect(hCanvasWnd, NULL, FALSE);
                        SendMessage(hCanvasWnd, WM_PAINT, uMsg, pointId);

                        wchar_t tempTextBuffer[sizeof(L"Add Point %i, %i")];

                        wsprintfW(tempTextBuffer, L"Add Point %i, %i", currentPosition.x, currentPosition.y);

                        AppFunctions::TextOutput(MyObjects.Output.hObjectWnd, tempTextBuffer);

                        CurrentToolState = ToolState::empty;

                        break;
                    }
                }
            // If current mouse position was found in data storage ...
            } else {
                // ... set active point flag.
                activePointId = pointId;
                activePointFlag = true;

                // Update selection state if point if it is not already 
                // selected. 
                if (MyDataStorage.CanvasData[pointId].selectionState != 2) {
                    AppFunctions::ResetSelection();
                    POINT pointToSelect = AppFunctions::UpdateSelectionState(pointId, 2);

                    InvalidateRect(hCanvasWnd, NULL, FALSE);
                    SendMessage(hCanvasWnd, WM_PAINT, uMsg, -1);

                    // The new operator allocates and initializes an 
                    // array of wchar_t characters and returns a 
                    // pointer to it.
                    LPWSTR tempTextBuffer = new wchar_t[sizeof(L"Select Point %i, %i")];

                    wsprintfW(tempTextBuffer, L"Select Point %i, %i", pointToSelect.x, pointToSelect.y);

                    AppFunctions::TextOutput(MyObjects.Output.hObjectWnd, tempTextBuffer);

                    // Use the delete operator to deallocate the memory 
                    // allocated by the new operator.
                    delete[] tempTextBuffer;
                }
            }

            TRACKMOUSEEVENT trackMouseEvent = {
                sizeof(TRACKMOUSEEVENT),
                TME_HOVER,
                hCanvasWnd,
                10
            };

            TrackMouseEvent(&trackMouseEvent);

            break;
        }

        case WM_RBUTTONDOWN:
        {
            AppFunctions::ResetSelection();

            InvalidateRect(hCanvasWnd, NULL, FALSE);
            SendMessage(hCanvasWnd, WM_PAINT, NULL, NULL);

            break;
        }

        case WM_LBUTTONUP:
        {
            // ...

            break;
        }

        case WM_MOUSEMOVE:
        {
            // Initialize a mouse tracking event every time the mouse 
            // moves. The tracking event stops when the window which 
            // handle is specified registers a "WM_MOUSEHOVER"-Message.
            TRACKMOUSEEVENT trackMouseEvent = {
                sizeof(TRACKMOUSEEVENT),
                TME_HOVER,
                hCanvasWnd,
                10
            };

            TrackMouseEvent(&trackMouseEvent);

            break;
        }

        case WM_MOUSEHOVER:
        {
            INT32 xValue, yValue;

            xValue = GET_X_LPARAM(lParam);
            yValue = GET_Y_LPARAM(lParam);

            POINT currentPosition = {
                GET_X_LPARAM(lParam),
                GET_Y_LPARAM(lParam)
            };

            int pointId = AppFunctions::SearchDataStorage(currentPosition);

            // If the current mouse position was not found in data 
            // storage ... 
            if (pointId == -1) {
                // ... the further processing is done just if the active 
                // point flag is set additionally.
                if (activePointFlag) {
                    int selectionState = MyDataStorage.CanvasData[activePointId].selectionState;

                    switch (selectionState) {
                        case 0:
                        {

                            break;
                        }
                        // In case the state of the active point is 1 the 
                        // selection state is reset.
                        case 1:
                        {
                            AppFunctions::UpdateSelectionState(activePointId, 0);

                            InvalidateRect(hCanvasWnd, NULL, FALSE);
                            SendMessage(hCanvasWnd, WM_PAINT, uMsg, activePointId);

                            activePointId = -1;
                            activePointFlag = false;

                            break;
                        }
                        // If selection state of the active point is 2 the 
                        // point the further processing depends on the state 
                        // of the left mouse button: If it is down the active 
                        // point is repositioned, otherways it gets 
                        // deactivated.
                        case 2:
                        {
                            if (GetKeyState(VK_LBUTTON) < 0) {
                                MyDataStorage.CanvasData[activePointId].position.x = currentPosition.x;
                                MyDataStorage.CanvasData[activePointId].position.y = currentPosition.y;

                                InvalidateRect(hCanvasWnd, NULL, FALSE);
                                SendMessage(hCanvasWnd, WM_PAINT, NULL, -1);
                            } else {
                                activePointId = -1;
                                activePointFlag = false;
                            }

                            break;
                        }
                    }

                }
            // If the current mouse position was found in data storage ...
            } else {
                // ... the further processing depends on the selection state 
                // of the corresponding point.
                int selectionState = MyDataStorage.CanvasData[pointId].selectionState;

                switch (selectionState) {
                    case 0:
                    {
                        AppFunctions::UpdateSelectionState(pointId, 1);

                        activePointId = pointId;
                        activePointFlag = true;

                        InvalidateRect(hCanvasWnd, NULL, FALSE);
                        SendMessage(hCanvasWnd, WM_PAINT, uMsg, pointId);

                        break;
                    }
                    case 1:
                    {

                        break;
                    }
                    case 2:
                    {

                        break;
                    }
                }
            }

            break;
        }

        case WM_DESTROY:
        {

            break;
        }
    }

    return DefWindowProc(hCanvasWnd, uMsg, wParam, lParam);
}
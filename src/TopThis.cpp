// TopThis.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TopThis.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TOPTHIS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TOPTHIS));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TOPTHIS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TOPTHIS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   BOOL bSuccess = TRUE;
   hInst = hInstance; // Store instance handle in our global variable

   //
   // Main Window
   //
   RECT workingArea;
   BOOL bFoundWorkingArea = SystemParametersInfo(SPI_GETWORKAREA, 0, &workingArea, 0);
   if (!bFoundWorkingArea)
   { 
      bSuccess = FALSE;
   }

   LONG workingAreaWidth = workingArea.right - workingArea.left;
   LONG workingAreaHeight = workingArea.bottom - workingArea.top;

   LONG windowX = workingAreaWidth * 7/10;
   LONG windowY = workingAreaHeight * 3/5;
   LONG windowWidth = workingAreaWidth * 3/10;
   LONG windowHeight = workingAreaHeight * 2/5;

   HWND hWnd = CreateWindowW(
      szWindowClass, 
      szTitle, 
      WS_OVERLAPPEDWINDOW,
      windowX, 
      windowY, 
      windowWidth, 
      windowHeight, 
      nullptr, 
      nullptr, 
      hInstance, 
      nullptr
   );
   if (!hWnd) { bSuccess = FALSE; }
   
   SetWindowText(hWnd, (LPCWSTR)applicationTitle);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   
   {
      //
      // List Box
      //
      int box_x = 10;
      int box_y = 35;
      int box_width = 500;
      int box_height = 255;

      hListBox = CreateWindowEx(
         WS_EX_CLIENTEDGE, 
         _T("LISTBOX"),
         NULL, 
         WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, 
         box_x, 
         box_y, 
         box_width, 
         box_height, 
         hWnd, 
         NULL, 
         hInst, 
         NULL
      );
      if (!hListBox) { bSuccess = FALSE; }
   }

   {
      //
      // Set To Top Button
      //
      int but_x = 10;
      int but_y = 300;
      int but_width = 60;
      int but_height = 25;

      hApplyButton = CreateWindow(
         _T("BUTTON"), // Control type
         L"Apply", // Name
         WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_TEXT, // Style flags
         but_x, 
         but_y, 
         but_width, 
         but_height, 
         hWnd, // Parent window
         (HMENU)IDC_BTN_APPLY, // This control's ID (used in WndProc)
         hInst, // Current instance
         NULL
      );
      if (!hApplyButton) { bSuccess = FALSE; }
   }

   {
      //
      // Resume normal window behavior Button
      //
      int but_x = 80;
      int but_y = 300;
      int but_width = 60;
      int but_height = 25;

      hClearButton = CreateWindow(
         _T("BUTTON"),
         L"Clear", 
         WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_TEXT, 
         but_x, 
         but_y, 
         but_width, 
         but_height, 
         hWnd, 
         (HMENU)IDC_BTN_CLEAR, 
         hInst, 
         NULL
      );
      if (!hClearButton) { bSuccess = FALSE; }
   }

   {
      //
      // Update window list Button
      //
      int but_x = 150;
      int but_y = 300;
      int but_width = 85;
      int but_height = 25;

      hUpdateButton = CreateWindow(
         _T("BUTTON"),
         L"Update List", 
         WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON | BS_TEXT, 
         but_x, 
         but_y, 
         but_width, 
         but_height, 
         hWnd, 
         (HMENU)IDC_BTN_UPDATELIST, 
         hInst, 
         NULL
      );
      if (!hUpdateButton) { bSuccess = FALSE; }
   }

   {
      //
      // Instruction Message
      //

      int msg_x = 10;
      int msg_y = 15;
      int msg_width = 500;
      int msg_height = 18;

      hInstructionMessage = CreateWindow(
         _T("STATIC"), 
         L"Select a window and click 'Apply'", 
         WS_CHILD | WS_VISIBLE | SS_LEFT, 
         msg_x, 
         msg_y, 
         msg_width, 
         msg_height, 
         hWnd, 
         (HMENU)IDC_INSTRUCTIONMSG, 
         hInst, 
         NULL
      );
      if (!hInstructionMessage) { bSuccess = FALSE; }
   }

   {
      //
      // Status Message
      //
      int msg_x = 10;
      int msg_y = 335;
      int msg_width = 500;
      int msg_height = 18;

      hStatusMessage = CreateWindow(
         _T("STATIC"), 
         L"HELLO I AM STATUS MESSAGE BEEP BOOP", 
         WS_CHILD | WS_VISIBLE | SS_LEFT, 
         msg_x,
         msg_y,
         msg_width,
         msg_height,
         hWnd,
         (HMENU)IDC_STATUSMSG, 
         hInst, 
         NULL
      );
      if (!hStatusMessage) { bSuccess = FALSE; }
   }
   
   EnumWindows(EnumWindowsCallback, NULL); // Add open windows to list.

   return bSuccess;
}

static BOOL CALLBACK EnumWindowsCallback(IN HWND hWnd, IN LPARAM lParam)
{
   if (!IsWindowVisible(hWnd) || GetWindow(hWnd, GW_OWNER) != NULL)
   { return TRUE; }

   if (0 != GetWindowTextLength(hWnd))
   {
      /// there we have a "true" window
      BOOL bAddToList = TRUE;
      TCHAR title[256];
      GetWindowText(hWnd, title, sizeof(title));
      for (HWND element : openWindows)
      {
         TCHAR existingTitle[256];
         GetWindowText(element, existingTitle, sizeof(existingTitle));
         if (0 == _tcscmp(existingTitle, title)) // Is 0 if strings are identical.
         { 
            bAddToList = FALSE;
            break; 
         }
      }

      if (0 == _tcscmp(applicationTitle, title)) { bAddToList = FALSE; }
      if (0 == _tcscmp(TEXT("Program Manager"), title)) { bAddToList = FALSE; }
  
    if (bAddToList) { AddToOpenWindowsList(hWnd, title); }
   }

   return TRUE;
}

void AddToOpenWindowsList(HWND &hWnd, TCHAR  title[256])
{
   openWindows.push_back(hWnd);
   SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)title);
}

HWND GetSelectedHWND()
{
   LRESULT selectedIndex = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
   return openWindows[selectedIndex];
}

void SetToTop(HWND &hWnd)
{
   if (!bForceToTop) { return; }

   DWORD procID = 0;
   procID = GetWindowThreadProcessId(hWnd, OUT(LPDWORD)procID);
   TCHAR title[256];
   GetWindowText(hWnd, (LPWSTR)title, sizeof(title));
   
   ShowWindow(hWnd, (int)SW_RESTORE);
   SetWindowPos(
      hWnd, 
      HWND_TOPMOST, 
      100, // ignored by SWP_NOMOVE
      100, // ignored by SWP_NOMOVE
      700, // ignored by SWP_NOMOVE
      500, // ignored by SWP_NOMOVE
      SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE
   );

   TCHAR szStatusText[1024];
   swprintf_s(szStatusText, TEXT("'%s' set to be always on top."), title);
   SetWindowText(hStatusMessage, (LPCWSTR)szStatusText);
}

void MaybeClearTop()
{
   if (hWndToKeepOnTop)
   {
      SetWindowText(
         hStatusMessage, 
         L"Always-on-top status cleared. Resumed normal window behavior."
      );
      SetWindowPos(
         hWndToKeepOnTop, 
         HWND_NOTOPMOST, 
         100, // ignored by SWP_NOMOVE
         100, // ignored by SWP_NOMOVE
         700, // ignored by SWP_NOMOVE
         500, // ignored by SWP_NOMOVE
         SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE
      );
   }
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            
            switch (wmId)
            {
            // Parse button presses:
            case IDC_BTN_APPLY:
               bForceToTop = TRUE;
               MaybeClearTop();
               hWndToKeepOnTop = GetSelectedHWND();
               SetToTop(hWndToKeepOnTop);
               break;
            case IDC_BTN_CLEAR:
               bForceToTop = FALSE;
               MaybeClearTop();
               break;
            case IDC_BTN_UPDATELIST:
               openWindows.clear();
               SendMessage(hListBox, LB_RESETCONTENT, 0, 0);
               EnumWindows(EnumWindowsCallback, NULL);
               MaybeClearTop();
               SetWindowText(
                  hStatusMessage, 
                  L"Window list updated. Always-on-top status cleared."
               );
               break;
               
            // Parse the menu selections:
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
               MaybeClearTop();
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_WINDOWPOSCHANGED:
       if (bForceToTop && hWndToKeepOnTop) { SetToTop(hWndToKeepOnTop); }
       break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
       MaybeClearTop();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include "resource.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

TCHAR applicationTitle[256] = TEXT("Top This");

HWND hListBox;
HWND hApplyButton;
HWND hClearButton;
HWND hUpdateButton;
HWND hInstructionMessage;
HWND hStatusMessage;

HWND hWndToKeepOnTop;
BOOL bForceToTop = FALSE;


std::vector<HWND> openWindows = std::vector<HWND>();

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HBRUSH windowBackgroundColor = CreateSolidBrush(RGB(100, 120, 150));

static BOOL CALLBACK EnumWindowsCallback(IN HWND hWnd, IN LPARAM lParam);
static void AddToOpenWindowsList(HWND &hWnd, TCHAR title[256]);

HWND GetSelectedHWND();
void SetToTop(HWND &hWnd);
void MaybeClearTop();


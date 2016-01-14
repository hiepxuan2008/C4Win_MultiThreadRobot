// P3_1312206.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "P3_1312206.h"
#include "AppController.h"
#include <CommCtrl.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	HowToUse(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	ProcSettings(HWND, UINT, WPARAM, LPARAM);

#include <iostream>
#include <io.h>
#include <fcntl.h>

void initConsole();

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	//initConsole();

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_P3_1312206, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_P3_1312206));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_P3_1312206));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_P3_1312206);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, SW_MAXIMIZE);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_HELP_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_HELP_HOWTOUSE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_HOWTOUSE), hWnd, About);
			break;
		case ID_SETTINGS:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SETTINGS), hWnd, ProcSettings);
			break;
		case ID_START:
			AppController::getInstance()->OnStart();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
					 hdc = BeginPaint(hWnd, &ps);
					 RECT rect;
					 int nWidth, nHeight;
					 GetClientRect(hWnd, &rect);
					 nWidth = rect.right - rect.left;
					 nHeight = rect.bottom - rect.top;

					 HDC hMemDC = CreateCompatibleDC(hdc);
					 HBITMAP hBitmap = CreateCompatibleBitmap(hdc, nWidth, nHeight);
					 HGDIOBJ hBmpOld = SelectObject(hMemDC, hBitmap);
					 FillRect(hMemDC, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

					 //Draw shapes to hMemDC
					 AppController::getInstance()->Draw(hMemDC);

					 //Copy data from hMemDC to hdc
					 BitBlt(hdc, 0, 0, nWidth, nHeight, hMemDC, 0, 0, SRCCOPY);

					 //Release memory
					 SelectObject(hMemDC, hBmpOld);
					 DeleteObject(hBitmap);
					 DeleteObject(hMemDC);

					 EndPaint(hWnd, &ps);
	}
		break;
	case WM_CREATE:
		AppController::getInstance()->Initialize(hWnd, hInst);
		break;
	case WM_SIZE:
		AppController::getInstance()->OnSize();
		break;
	case WM_DESTROY:
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

INT_PTR CALLBACK HowToUse(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

INT_PTR CALLBACK	ProcSettings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
	{
						  WCHAR buff[10];
						  wsprintf(buff, L"%d", AppController::getInstance()->numberOfBucket);
						  SetDlgItemText(hDlg, IDC_EDIT_SETTINGS_BUCKET_NUM, buff);

						  wsprintf(buff, L"%d", AppController::getInstance()->movingSpeed);
						  SetDlgItemText(hDlg, IDC_STATIC_MOVINGSPEED, buff);

						  SendMessage(GetDlgItem(hDlg, IDC_SLIDER_SPEED), TBM_SETRANGE,
							  (WPARAM)TRUE,                   // redraw flag 
							  (LPARAM)MAKELONG(1, 10));  // min. & max. positions

						  SendMessage(GetDlgItem(hDlg, IDC_SLIDER_SPEED), TBM_SETPOS,
							  (WPARAM)TRUE, (LPARAM)AppController::getInstance()->movingSpeed);

	}
		return (INT_PTR)TRUE;
		//https://msdn.microsoft.com/en-us/library/windows/desktop/bb760149(v=vs.85).aspx#tkb_notifications
	case WM_HSCROLL: //Trackbar changing notifications
	{
						 int iPos = 0;
						 HWND hTrackBar = (HWND)lParam;
						 if (hTrackBar == GetDlgItem(hDlg, IDC_SLIDER_SPEED))
						 {
							 iPos = SendMessage(hTrackBar, TBM_GETPOS, 0, 0);
							 AppController::getInstance()->OnChangeSliderSpeed(hDlg, iPos);
							 std::cout << iPos << std::endl;
						 }
						 
						 break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDOK:
		{
					 WCHAR buff[10];
					 GetDlgItemText(hDlg, IDC_EDIT_SETTINGS_BUCKET_NUM, buff, ARRAYSIZE(buff));
					 AppController::getInstance()->numberOfBucket = _wtoi(buff);
		
					 EndDialog(hDlg, LOWORD(wParam));
					 return (INT_PTR)TRUE;
		}
			break;

		default:
			break;
		}
	}
	return (INT_PTR)FALSE;
}

void initConsole()
{
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;

	std::cout << "Console for debugging" << std::endl;
}
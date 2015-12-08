// rasterizer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "rasterizer.h"
#include "softrender.h"

#define MAX_LOADSTRING	100
#define WIDTH			800
#define HEIGHT			600

// Global Variables:

HINSTANCE	hInst;								// current instance
TCHAR		szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR		szWindowClass[MAX_LOADSTRING];			// the main window class name
bool		g_bExit = false;
HWND		g_hWnd;
HGDIOBJ		g_screenDIB;
HBITMAP		g_dibBefore; 
HDC			g_dbiDc;
char*		g_screenBits;

SoftRender g_softRender;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void				Update();
void				Draw();
void				initDIB(HDC dibDC, int width, int height);
void				releaseDIB(HDC dibDC);



int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RASTERIZER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RASTERIZER));

	// Main message loop:
	while (!g_bExit)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				g_bExit = true;
			}
			else					
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		Update();		
		Draw();
	}

	return (int) msg.wParam;
}

void Update()
{

}

void Draw()
{
	g_softRender.clear(0x00000000);
	g_softRender.drawLine(0, 0, 100, 100, 0x00ffffff);

	const FrameBuffer& fb = g_softRender.getBackBuffer();
	memcpy(g_screenBits, fb.m_dwColorBuffer, fb.m_iWidth * fb.m_iHight * sizeof(DWORD));
	BitBlt(GetDC(g_hWnd), 0, 0, fb.m_iWidth, fb.m_iHight, g_dbiDc, 0, 0, SRCCOPY);
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RASTERIZER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_RASTERIZER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   //hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      //CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   g_hWnd = hWnd;

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_SIZE:
		{
			int iWidth = LOWORD(lParam);
			int iHeight = HIWORD(lParam);
			g_softRender.resize(iWidth, iHeight);
			g_dbiDc = CreateCompatibleDC(GetDC(hWnd));
			releaseDIB(g_dbiDc);
			initDIB(g_dbiDc, iWidth, iHeight);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	case WM_DESTROY:
		DeleteObject(g_dbiDc);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

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

void initDIB(HDC dibDC, int width, int height)
{  
	BITMAPINFO bmi;  
	memset(&bmi, 0, sizeof(bmi));  
	bmi.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);  
	bmi.bmiHeader.biWidth		= width;  
	bmi.bmiHeader.biHeight		= -height;  
	bmi.bmiHeader.biPlanes		= 1;
	bmi.bmiHeader.biBitCount	= 32;  
	bmi.bmiHeader.biCompression	= BI_RGB;  
	g_screenDIB = CreateDIBSection(NULL, &bmi, DIB_RGB_COLORS, (void**)&g_screenBits, NULL, 0);  
	g_dibBefore = (HBITMAP)SelectObject(dibDC, g_screenDIB);  
}  

void releaseDIB(HDC dibDC)
{  
	if(g_screenDIB!=NULL)
	{
		SelectObject(dibDC, g_dibBefore);
		DeleteObject(g_screenDIB);  
		g_screenDIB=NULL; 
	}  
}  
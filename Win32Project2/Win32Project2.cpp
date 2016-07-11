#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#include <vector>
using namespace std;

#include "InputManager.h"
#include "ObjectManager.h"
#include "GraphicsManager.h"
#include "Vector3d.h"
#include "LineSegment2d.h"
#include "GraphicsModule.h"
#include "GameObject.h"
#include "Player.h"

bool quit = false;

LONG clientWidth, clientHeight;

LARGE_INTEGER lastFrameMicroseconds = { 0 };
LONGLONG frameTime = (LONGLONG)(1000000 / 24);

RECT window = { 100,100,600,600 };

void initializeGame() {
	ObjectManager::getInstance()->addObject(new Player(Vector3d(0.5,0.5,0.0)));
}

void update() {
	InputManager::getInstance()->update();
	ObjectManager::getInstance()->update();
}

LARGE_INTEGER getCurrentMicros() {
	LARGE_INTEGER Time;
	LARGE_INTEGER Frequency;

	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&Time);

	//
	// We now have the elapsed number of ticks, along with the
	// number of ticks-per-second. We use these values
	// to convert to the number of elapsed microseconds.
	// To guard against loss-of-precision, we convert
	// to microseconds *before* dividing by ticks-per-second.
	//

	Time.QuadPart *= 1000000;
	Time.QuadPart /= Frequency.QuadPart;

	return Time;
}

VOID OnPaint(HDC hdc)
{
	Graphics g(hdc);
	GraphicsManager::getInstance()->update(g);	
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
	HWND                hWnd;
	MSG                 msg;
	WNDCLASS            wndClass;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;

	// Initialize GDI+.
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = TEXT("GettingStarted");

	RegisterClass(&wndClass);

	hWnd = CreateWindow(
		TEXT("GettingStarted"),   // window class name
		TEXT("Getting Started"),  // window caption
		WS_OVERLAPPEDWINDOW,      // window style
		CW_USEDEFAULT,            // initial x position
		CW_USEDEFAULT,            // initial y position
		CW_USEDEFAULT,            // initial x size
		CW_USEDEFAULT,            // initial y size
		NULL,                     // parent window handle
		NULL,                     // window menu handle
		hInstance,                // program instance handle
		NULL);                    // creation parameters

	ShowWindow(hWnd, iCmdShow);
	UpdateWindow(hWnd);

	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	clientHeight = clientRect.bottom - clientRect.top;
	clientWidth = clientRect.right - clientRect.left;

	initializeGame();

	while (!quit) {

		LARGE_INTEGER currentMicros = getCurrentMicros();
		LONGLONG diff = currentMicros.QuadPart - lastFrameMicroseconds.QuadPart;
		if (diff > frameTime) {
			lastFrameMicroseconds = currentMicros;
			
			update();

			InvalidateRect(hWnd, NULL, FALSE);
		}

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);
	return (int)(msg.wParam);
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		OnPaint(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		quit = true;
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
} // WndProc

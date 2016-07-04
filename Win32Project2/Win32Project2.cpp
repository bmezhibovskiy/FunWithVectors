#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

#include <vector>
using namespace std;

#include "Vector3d.h"

bool quit = false;

LONG clientWidth, clientHeight;

LARGE_INTEGER lastFrameMicroseconds = { 0 };
LONGLONG frameTime = (LONGLONG)(1000000 / 16);

RECT window = { 100,100,600,600 };

bool previousKeys[255] = { false };
bool pressedKeys[255] = { false };
bool triggeredKeys[255] = { false };

struct LineSegment2d {
	Vector3d start, end;
	LineSegment2d(double x1, double y1, double x2, double y2) : start(x1, y1, 0), end(x2, y2, 0) {}
};

struct Player {
	Vector3d position;
	Vector3d velocity;
	Vector3d acceleration;
	Player() : position(0.5, 0.5, 0.0), velocity(0, 0, 0), acceleration(0, 0, 0) {}
};

vector<LineSegment2d> linesToDraw;
Player player;

void updateInput() {
	for (int i = 0; i < 255; ++i) {
		previousKeys[i] = pressedKeys[i];
		pressedKeys[i] = GetAsyncKeyState(i) & 0x8000;
		triggeredKeys[i] = (previousKeys[i] == false && pressedKeys[i] == true);
	}
}

void update() {

	double speed = 0.0025;
	player.acceleration = Vector3d(0, 0, 0);
	if (pressedKeys[VK_UP]) {
		player.acceleration = player.acceleration + Vector3d(0, -speed, 0);
	}
	if (pressedKeys[VK_DOWN]) {
		player.acceleration = player.acceleration + Vector3d(0, speed, 0);
	}
	if (pressedKeys[VK_LEFT]) {
		player.acceleration = player.acceleration + Vector3d(-speed, 0, 0);
	}
	if (pressedKeys[VK_RIGHT]) {
		player.acceleration = player.acceleration + Vector3d(speed, 0, 0);
	}

	double epsilon = 1e-8;
	if (player.velocity.lengthSquared() > epsilon) {
		double playerFriction = -0.2;
		Vector3d friction = player.velocity * playerFriction;
		player.acceleration = player.acceleration + friction;
	}
	else {
		player.velocity = Vector3d(0, 0, 0);
	}

	player.velocity = player.velocity + player.acceleration;
	player.position = player.position + player.velocity;

	if (player.velocity.lengthSquared() > 0.0) {
		Vector3d nextFramePosition = player.position + (player.velocity.normalized() * 0.025);
		LineSegment2d playerRepresentation = LineSegment2d(player.position.x, player.position.y, nextFramePosition.x, nextFramePosition.y);
		linesToDraw.push_back(playerRepresentation);
	}
	else {
		double size = 0.01;
		LineSegment2d playerRepresentationA = LineSegment2d(player.position.x-size, player.position.y, player.position.x+size, player.position.y);
		LineSegment2d playerRepresentationB = LineSegment2d(player.position.x, player.position.y-size, player.position.x, player.position.y+size);
		linesToDraw.push_back(playerRepresentationA);
		linesToDraw.push_back(playerRepresentationB);
	}
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

void drawBorder(Graphics& g) {
	Pen pen(Color(0, 0, 0), 2.0f);
	g.DrawLine(&pen, 100, 100, 600, 100);
	g.DrawLine(&pen, 100, 600, 600, 600);
	g.DrawLine(&pen, 100, 100, 100, 600);
	g.DrawLine(&pen, 600, 100, 600, 600);
}

void drawLine(Graphics& g, Color c, LineSegment2d ls) {
	Pen pen(c, 3.0f);
	g.DrawLine(&pen, (INT)(ls.start.x * 500 + 100), (INT)(ls.start.y * 500 + 100), (INT)(ls.end.x * 500 + 100), (INT)(ls.end.y * 500 + 100));
}

VOID OnPaint(HDC hdc)
{
	Graphics g(hdc);
	g.Clear(Color(255, 255, 255));
	drawBorder(g);
	size_t numLines = linesToDraw.size();
	for(size_t i = 0; i < numLines; ++i) {
		drawLine(g, Color(50, 60, 200), linesToDraw[i]);
	}
	linesToDraw.clear();
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

	while (!quit) {

		

		LARGE_INTEGER currentMicros = getCurrentMicros();
		LONGLONG diff = currentMicros.QuadPart - lastFrameMicroseconds.QuadPart;
		if (diff > frameTime) {
			lastFrameMicroseconds = currentMicros;

			updateInput();

			update();

			InvalidateRect(hWnd, NULL, FALSE);
		}

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);
	return msg.wParam;
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

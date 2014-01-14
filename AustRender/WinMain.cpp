#include <Windows.h>

//temp for showing render
#include "dxinput.h"
#include "DirectXFrame.h"


//fullscreen res
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
//windowed res
#define W_SCREEN_WIDTH 800
#define W_SCREEN_HEIGHT 600

#define WINDOW_TITLE L"EeveeHound"


HWND				g_hWnd;			// Handle to the window
HINSTANCE			g_hInstance;	// Handle to the application instance
bool				g_bWindowed;	// Boolean for windowed or full-screen

// Entry point for the game or application.
int WINAPI wWinMain(HINSTANCE hInstance,	// Handle to the application
	HINSTANCE hPrevInstance,	// Handle to the previous app
	LPTSTR lpCmdLine,		// Command line string
	int lpCmdShow);			// Show window value

LRESULT CALLBACK WndProc(HWND hWnd,			// Handle to the window
	UINT message,		// Incoming Message
	WPARAM wparam,		// Message Info
	LPARAM lparam);	// Message Info

void InitWindow(void)
{
	WNDCLASSEX wndClass;  
	ZeroMemory(&wndClass, sizeof(wndClass));

	// set up the window
	wndClass.cbSize			= sizeof(WNDCLASSEX);			// size of window structure
	wndClass.lpfnWndProc	= (WNDPROC)WndProc;				// message callback
	wndClass.lpszClassName	= WINDOW_TITLE;					// class name
	wndClass.hInstance		= g_hInstance;					// handle to the application
	wndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);	// default cursor
	//wndClass.hbrBackground	= (HBRUSH)(COLOR_WINDOWFRAME);	// background brush

	// register a new type of window
	RegisterClassEx(&wndClass);
	DWORD style;
	int height, width;
	if(g_bWindowed)
	{
		style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
		width = W_SCREEN_WIDTH;
		height = W_SCREEN_HEIGHT;
	}
	else
	{
		style = WS_EX_TOPMOST | WS_POPUP;
		width = SCREEN_WIDTH;
		height = SCREEN_HEIGHT;
	}

	g_hWnd = CreateWindowEx(
		NULL,
		WINDOW_TITLE, WINDOW_TITLE, 							// window class name and title
		style,													// window style
		CW_USEDEFAULT, CW_USEDEFAULT,							// x and y coordinates
		width, height,											// width and height of window
		NULL, NULL,												// parent window and menu
		g_hInstance,											// handle to application
		NULL);

	// Display the window
	ShowWindow(g_hWnd, SW_SHOW);
	UpdateWindow(g_hWnd);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	g_hInstance = hInstance;	// Store application handle
	g_bWindowed = true;		// Windowed mode or full-screen
	bool push = false;
	// Init the window
	InitWindow();
	MSG msg; 
	ZeroMemory(&msg, sizeof(msg));
	dxinputframe input;
	DirectXFrame display;
	cam temp;
	char keyboard[256];
	DIMOUSESTATE2 mouse;
	input.init(g_hWnd,g_hInstance);
	display.Init(g_hWnd,g_hInstance,g_bWindowed);
	//Main Loop
	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		input.Update(keyboard,mouse);
		display.Render(temp,NULL,0,NULL,0,NULL,0);
	}
	display.Shutdown();
	input.ShutDown();
	// Unregister window
	UnregisterClass(WINDOW_TITLE, g_hInstance);

	// Return successful
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	// attempt to handle your messages
	switch(message)
	{
	case (WM_PAINT):
		{
			InvalidateRect(hWnd,NULL,TRUE);
			break;
		}		
	case(WM_DESTROY):
		{
			PostQuitMessage(0); 
			break;
		}
	case(WM_KEYDOWN):
		{
			switch(wparam)
			{
				// Escape Key will close the application
				// Remove/Modify this call when creating a real game with menus, etc.
				case VK_ESCAPE:
				{
				PostQuitMessage(0);
				break;
				}
			}
		}
	}

	// pass to default handler
	return DefWindowProc(hWnd, message, wparam, lparam);
}

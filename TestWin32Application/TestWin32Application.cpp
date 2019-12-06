#include "framework.h"
#include "TestWin32Application.h"
#include "../CommonUtilities/InputHandler.h"
#include <string>
#include <thread>
#include <chrono>

#define MAX_LOADSTRING 100

using namespace std::chrono_literals;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND globalWindow;
CommonUtilities::InputHandler globalInputHandler;
bool globalIsRunning = true;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TESTWIN32APPLICATION, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	MSG msg = {0};

	MessageBoxW(globalWindow,
		L"Input Test\n\n"
		"Key: W     \t - Kolla om en specifik tangent är nedtryckt just nu.\n"
		"Key: Space \t - Kolla om en specifik tangent precis blev nedtryckt.\n"
		"Key: Space \t - Kolla om en specifik tangent precis släpptes upp. \n"
		"Key: LMouse\t - Kolla musknapp precis nertryckt och musposition.\n"
		"Key: LMouse\t - Kolla musknapp precis släpptes upp.\n"
		"Key: RMouse\t - Kolla musknapp nertryckt.\n"
		"Key: A      \t - Kolla musens delta.\n"
		"Key: S      \t - Sätt musens position (200,200)\n"
		"\nTryck F2 för att öppna hjälp boxen.",
		L"Help", 0);

	while (globalIsRunning)
	{
		globalInputHandler.ClearFrame();
		while (PeekMessageW(&msg, globalWindow, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// Gameloop starts
		if (globalInputHandler.GetKey(CommonUtilities::KeyCode::W))
		{
			OutputDebugStringW(L"GetKey held\n");
		}
		if (globalInputHandler.GetKeyDown(CommonUtilities::KeyCode::Space))
		{
			OutputDebugStringW(L"GetKeyDown\n");
		}
		if (globalInputHandler.GetKeyUp(CommonUtilities::KeyCode::Space))
		{
			OutputDebugStringW(L"GetKeyUp\n");
		}
		if (globalInputHandler.GetMouseButton(CommonUtilities::MouseButton::Right))
		{
			OutputDebugStringW(L"GetMouseButton Held\n");
		}
		if (globalInputHandler.GetMouseButtonDown(CommonUtilities::MouseButton::Left))
		{
			OutputDebugStringW(L"GetMouseLeftDown\n");
			OutputDebugStringW(std::wstring(L"{Cursor X:" + std::to_wstring(globalInputHandler.GetMouseX()) + L" Y: " + std::to_wstring(globalInputHandler.GetMouseY()) + L"}\n").c_str());
		}
		if (globalInputHandler.GetMouseButtonUp(CommonUtilities::MouseButton::Left))
		{
			OutputDebugStringW(L"GetMouseLeftUp\n");
		}
		if (globalInputHandler.GetKeyDown(CommonUtilities::KeyCode::S))
		{
			OutputDebugStringW(std::wstring(L"Before: {Cursor X:" + std::to_wstring(globalInputHandler.GetMouseX()) + L" Y: " + std::to_wstring(globalInputHandler.GetMouseY()) + L"}\n").c_str());
			globalInputHandler.SetCursorPosition(globalWindow, 200, 200);
			OutputDebugStringW(std::wstring(L"After: {Cursor X:" + std::to_wstring(globalInputHandler.GetMouseX()) + L" Y: " + std::to_wstring(globalInputHandler.GetMouseY()) + L"}\n").c_str());
		}
		const int delta = globalInputHandler.GetMouseWheelDelta();
		if (delta < 0)
		{
			OutputDebugStringW(L"Mouse wheeled down\n");
		}
		else if (delta > 0)
		{
			OutputDebugStringW(L"Mouse wheeled up\n");
		}
		if (globalInputHandler.GetKeyDown(CommonUtilities::KeyCode::F2))
		{
			MessageBoxW(globalWindow,
				L"Input Test\n\n"
				"Key: W     \t - Kolla om en specifik tangent är nedtryckt just nu.\n"
				"Key: Space \t - Kolla om en specifik tangent precis blev nedtryckt.\n"
				"Key: Space \t - Kolla om en specifik tangent precis släpptes upp. \n"
				"Key: LMouse\t - Kolla musknapp precis nertryckt och musposition.\n"
				"Key: LMouse\t - Kolla musknapp precis släpptes upp.\n"
				"Key: RMouse\t - Kolla musknapp nertryckt.\n"
				"Key: A      \t - Kolla musens delta.\n"
				"Key: S      \t - Sätt musens position (200,200)\n"
				"\nTryck F2 för att öppna hjälpboxen igen.",
				L"Help", 0);
		}
		std::this_thread::sleep_for(33ms);
	}

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = nullptr;
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TESTWIN32APPLICATION);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   globalWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!globalWindow)
   {
      return FALSE;
   }

   ShowWindow(globalWindow, nCmdShow);
   UpdateWindow(globalWindow);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (globalInputHandler.UpdateEvents(message, wParam, lParam))
	{
		return 0;
	}
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_DESTROY:
		globalIsRunning = false;
		break;
    default:
		break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

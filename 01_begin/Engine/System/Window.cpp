#include "Window.h"
#include <iostream>

Window::Window()
{
	windowTitle = L"Vovo game engine v0.01";
	std::cout << "Window CREATED\n" << std::endl;
}

Window::~Window(void)
{
	std::cout << "Window DELETED\n" << std::endl;
}

void Window::createWindowRect(int screenWidth, int screenHeight)
{
    WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	windowHInstance = GetModuleHandle(NULL);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = &Window::windowProcessor;
    wc.hInstance = windowHInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
	wc.lpszMenuName = NULL;
    wc.lpszClassName = windowTitle;
	wc.cbSize = sizeof(WNDCLASSEX);
    RegisterClassEx(&wc);

	windowWidth = screenWidth;
	windowHeight = screenHeight;

	setScreenMode();

	windowRect = CreateWindowEx(WS_EX_APPWINDOW,
                          windowTitle,
						  windowTitle,
						  WS_OVERLAPPEDWINDOW,
						  windowPosX,
                          windowPosY,
						  windowWidth,
                          windowHeight,
                          NULL,
                          NULL,
                          windowHInstance,
                          NULL);

	ShowWindow(windowRect, SW_SHOW);
	SetForegroundWindow(windowRect);
	SetFocus(windowRect);

	ShowCursor(FALSE);
}

void Window::SetApplicationTitle(const LPCWSTR &title)
{
	windowTitle = title;
}

void Window::setScreenMode()
{
	if (FULL_SCREEN)
	{
		DEVMODE devModeScreenSettings;
		windowPosX = windowPosY = 0;
		ZeroMemory(&devModeScreenSettings, sizeof(devModeScreenSettings));
		devModeScreenSettings.dmSize = sizeof(devModeScreenSettings);
		devModeScreenSettings.dmPelsWidth = (unsigned long)windowWidth;
		devModeScreenSettings.dmPelsHeight = (unsigned long)windowHeight;
		devModeScreenSettings.dmBitsPerPel = 32;
		devModeScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&devModeScreenSettings, CDS_FULLSCREEN);
	}
	else
	{
		windowPosX = (GetSystemMetrics(SM_CXSCREEN) - windowWidth) / 2;
		windowPosY = (GetSystemMetrics(SM_CYSCREEN) - windowHeight) / 2;
	}
}

HWND Window::windowHandle() const
{
	return windowRect;
}

LRESULT CALLBACK Window::windowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            } break;
    }

    return DefWindowProc (hWnd, message, wParam, lParam);
}

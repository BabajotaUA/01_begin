#include "Window.h"
#include <iostream>
#include "Input.h"

Window::Window()
{
	windowTitle = L"Vovo game engine v0.01";
	std::cout << "Window CREATED\n" << std::endl;
}

Window::~Window(void)
{
    DestroyWindow(windowHandle);
	std::cout << "Window DELETED\n" << std::endl;
}

void Window::createWindowRect(int screenWidth, int screenHeight, bool fullScreen)
{
    WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	windowHInstance = GetModuleHandle(NULL);
    wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = Input::windowProcessor;
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

    setScreenMode(fullScreen);

	windowHandle = CreateWindowEx(WS_EX_APPWINDOW,
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

	ShowWindow(windowHandle, SW_SHOW);
	SetForegroundWindow(windowHandle);
	SetFocus(windowHandle);

	ShowCursor(FALSE);
}

HWND Window::getWindowHandle() const
{
    return windowHandle;
}

void Window::setWindowTitle(const LPCWSTR &title)
{
	windowTitle = title;
	SetWindowText(windowHandle, windowTitle);
}

void Window::setScreenMode(bool fullScreen)
{
	if (fullScreen)
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

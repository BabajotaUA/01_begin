#include "Window.h"
#include <iostream>

Window::Window(HINSTANCE& hInstance, int nCommandShow)
{
	windowHInstance = hInstance;
	windowNCommandShow = nCommandShow;
	windowTitle = L"Vovo game engine v0.01";
	std::cout << "Window CREATED\n";
}

Window::~Window(void)
{
	std::cout << "Window DELETED\n";
}

void Window::CreateGraphics3D(int width, int height)
{
	HWND hWnd;
    WNDCLASSEX wc;

    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = &Window::windowProcessor;
    wc.hInstance = windowHInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass1";

    RegisterClassEx(&wc);

    hWnd = CreateWindowEx(NULL,
                          L"WindowClass1",
						  windowTitle,
                          WS_OVERLAPPEDWINDOW,
                          300,
                          300,
						  width,
                          height,
                          NULL,
                          NULL,
                          windowHInstance,
                          NULL);

    ShowWindow(hWnd, windowNCommandShow);
}

void Window::SetApplicationTitle(const LPCWSTR &title)
{
	windowTitle = title;
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

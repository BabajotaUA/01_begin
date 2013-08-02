#include "Window.h"
#include <iostream>


Window::Window(HINSTANCE& hInstance, int nCommandShow)
{
	windowHInstance = hInstance;
	windowNCommandShow = nCommandShow;
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
                          L"Our First Windowed Program",
                          WS_OVERLAPPEDWINDOW,
                          300,
                          300,
						  width,
                          height,
                          NULL,
                          NULL,
                          windowHInstance,
                          NULL);

    // display the window on the screen
    ShowWindow(hWnd, windowNCommandShow);
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

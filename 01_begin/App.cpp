#include "Window/Window.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCommandLine, int nCommandShow)
{
	Window appWindow = Window(hInstance, nCommandShow);

	appWindow.CreateGraphics3D(800, 600);

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
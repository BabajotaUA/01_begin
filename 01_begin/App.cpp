#include "Engine\GraphicsStarter.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCommandLine, int nCommandShow)
{
    
	Window appWindow = Window(hInstance, nCommandShow);
    GraphicsStarter graphics = GraphicsStarter(appWindow);

	graphics.CreateGraphics3D(800, 600);

    MSG msg;
    while(TRUE)
    {
        if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if(msg.message == WM_QUIT)
                break;
        }
    }
    return msg.wParam;
}
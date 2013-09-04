#include "Engine.h"
#include <iostream>

Engine::Engine(void)
{
    std::cout << "Engine CREATED\n" << std::endl;
}

Engine::~Engine(void)
{
    std::cout << "Engine DELETED\n" << std::endl;
}

bool Engine::isRunning()
{
    MSG msg;
	if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if(msg.message == WM_QUIT)
			return false;
    }
    return graphics.isOK() & input.isOK();
}
#include "Input.h"
#include <iostream>

Input::Input(void)
{
	keys = std::vector<bool>(256, false);
	std::cout << "Input CREATED\n" << std::endl;
}

Input::~Input(void)
{
	std::cout << "Input DELETED\n" << std::endl;
}

bool Input::isKeyHit(unsigned short key)
{
	MSG systemInput;
	if(PeekMessage(&systemInput, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&systemInput);
        DispatchMessage(&systemInput);

        if(systemInput.message == WM_QUIT)
			return true;
    }
	return false;
}

void Input::keyDown(unsigned short key)
{
	keys[key] = true;
}

void Input::keyUp(unsigned short key)
{
	keys[key] = false;
}

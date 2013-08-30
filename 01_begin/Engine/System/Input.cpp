#include "Input.h"
#include <iostream>

Input::Input(void)
{
	ApplicationHandle = std::unique_ptr<Input>(this);
	keysDown = std::vector<bool>(256, false);
	keysHit = std::vector<bool>(256, false);
	std::cout << "Input CREATED\n" << std::endl;
}

Input::~Input(void)
{
	ApplicationHandle.release();
	std::cout << "Input DELETED\n" << std::endl;
}

bool Input::isKeyHit(unsigned char key)
{
	bool result = keysHit[key];
	keysHit[key] = false;
	return result;
}

bool Input::isKeyDown(unsigned char scanCode)
{
	return keysDown[scanCode];
}

bool Input::isMouseDown(unsigned char scanCode)
{
	return false;
}

void Input::keyDown(unsigned char key)
{
	keysDown[key] = true;
	keysHit[key] = true;
}

void Input::keyUp(unsigned char key)
{
	keysDown[key] = false;
	keysHit[key] = false;
}

LRESULT CALLBACK Input::windowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		default:
		{
			return ApplicationHandle->messageInterception(hWnd, message, wParam, lParam);
		}
	}
}

LRESULT CALLBACK Input::messageInterception(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_KEYDOWN:
			keyDown((unsigned int)wParam);
			return 0;

		case WM_KEYUP:
			keyUp((unsigned int)wParam);
			return 0;

		case WM_MBUTTONDOWN:


		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}



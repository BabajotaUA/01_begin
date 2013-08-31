#include "Input.h"
#include <iostream>

Input::Input(void)
{
	ApplicationHandle = std::unique_ptr<Input>(this);
	keysDown = std::vector<bool>(256, false);
	keysHit = std::vector<bool>(256, false);
    mouseDown = std::vector<bool>(6000, false);
    mouseHit = std::vector<bool>(6000, false);
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

bool Input::isMouseHit(unsigned char scanCode)
{
    bool result = mouseHit[scanCode];
    mouseHit[scanCode] = false;
    return result;
}

bool Input::isMouseDown(unsigned char scanCode)
{
    return mouseDown[scanCode];
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
			keysDown[(unsigned int)wParam] = keysHit[(unsigned int)wParam] = true;
			return 0;

		case WM_KEYUP:
			keysDown[(unsigned int)wParam] = keysHit[(unsigned int)wParam] = false;
			return 0;

		case WM_MBUTTONDOWN:
            mouseDown[(unsigned int)wParam] = mouseHit[(unsigned int)wParam] = true;
            return 0;

        case WM_MBUTTONUP:
            mouseDown[(unsigned int)wParam] = mouseHit[(unsigned int)wParam] = true;
            return 0;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
}



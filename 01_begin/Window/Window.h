#pragma once
#include <Windows.h>

class Window
{
public:
	Window(HINSTANCE&, int);
	virtual ~Window(void);

	void CreateGraphics3D(int width, int height);

private:
	HINSTANCE windowHInstance;
	int windowNCommandShow;

	static LRESULT CALLBACK windowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


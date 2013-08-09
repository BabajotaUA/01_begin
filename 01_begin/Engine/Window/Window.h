#pragma once
#include <Windows.h>

class Window
{
public:
	Window(HINSTANCE&, int);
	virtual ~Window(void);

    HWND CreateWindowRect(int width, int height);
	void SetApplicationTitle(const LPCWSTR &title);

private:
	HINSTANCE windowHInstance;
	LPCWSTR windowTitle;
	int windowNCommandShow;

	static LRESULT CALLBACK windowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};


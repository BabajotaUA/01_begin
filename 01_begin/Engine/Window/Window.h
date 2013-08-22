#pragma once
#include <Windows.h>

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;

class Window
{
public:
	Window();
	virtual ~Window(void);

    void createWindowRect(int width = 0, int height = 0);
	void setApplicationTitle(const LPCWSTR &title);
	HWND window();

private:
	HINSTANCE windowHInstance;
	HWND windowRect;
	LPCWSTR windowTitle;

	static LRESULT CALLBACK windowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
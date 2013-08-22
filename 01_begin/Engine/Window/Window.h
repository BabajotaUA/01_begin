#pragma once
#include <Windows.h>

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;

class Window
{
public:
	Window(void);
	virtual ~Window(void);
	void setApplicationTitle(const LPCWSTR &title);

protected:
	void createWindowRect(int width, int height);
	HWND windowHandle(void) const;

private:
	HINSTANCE windowHInstance;
	HWND windowRect;
	LPCWSTR windowTitle;
	int windowWidth, windowHeight, windowPosX, windowPosY;

	static LRESULT CALLBACK windowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	void setScreenMode();
};
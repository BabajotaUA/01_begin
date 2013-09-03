#pragma once

#include <Windows.h>
#include <memory>

class Window
{
public:
	Window(void);
	virtual ~Window(void);

	void setWindowTitle(const LPCWSTR &title);
    void createWindowRect(int width, int height, bool fullScreen);
    HWND getWindowHandle() const;

private:
    HWND windowHandle;
	HINSTANCE windowHInstance;
	LPCWSTR windowTitle;
	int windowWidth, windowHeight, windowPosX, windowPosY;

	void setScreenMode(bool fullScreen);
};
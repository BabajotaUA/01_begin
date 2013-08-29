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
	LRESULT CALLBACK messageInterception(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    HWND getWindowHandle() const;

private:
    HWND windowHandle;
	HINSTANCE windowHInstance;
	LPCWSTR windowTitle;
	int windowWidth, windowHeight, windowPosX, windowPosY;

	static LRESULT CALLBACK windowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void setScreenMode(bool fullScreen);
};

static std::unique_ptr<Window> ApplicationHandle;
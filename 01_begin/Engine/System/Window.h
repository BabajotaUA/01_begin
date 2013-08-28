#pragma once

#include "Input.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;

class Window
{
public:
	Window(void);
	virtual ~Window(void);

	Input input;

	void SetApplicationTitle(const LPCWSTR &title);
	bool isRunning();
	LRESULT CALLBACK messageInterception(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	void createWindowRect(int width, int height);
	HWND windowHandle(void) const;

private:
	HINSTANCE windowHInstance;
	HWND windowRect;
	LPCWSTR windowTitle;
	int windowWidth, windowHeight, windowPosX, windowPosY;
	MSG systemInput;

	void setScreenMode();
};

static LRESULT CALLBACK windowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
static Window* ApplicationHandle = nullptr;
#pragma once

#include <vector>
#include <memory>
#include <Windows.h>

class Input
{
public:
	Input(void);
	virtual ~Input(void);

	bool isKeyHit(unsigned char key);
	bool isKeyDown(unsigned char key);
	bool isMouseDown(unsigned char key);

	LRESULT CALLBACK messageInterception(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK windowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	std::vector<bool> keysDown;
	std::vector<bool> keysHit;

	void keyDown(unsigned char key);
	void keyUp(unsigned char key);
};

static std::unique_ptr<Input> ApplicationHandle;

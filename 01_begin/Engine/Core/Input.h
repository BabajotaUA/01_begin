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

    bool isMouseHit(unsigned char key);
	bool isMouseDown(unsigned char key);

    bool isOK() const;

	LRESULT CALLBACK messageInterception(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK windowProcessor(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    bool ok;
	std::vector<bool> keysDown;
	std::vector<bool> keysHit;
};

static std::unique_ptr<Input> ApplicationHandle;

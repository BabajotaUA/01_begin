#pragma once

#include <Windows.h>
#include <vector>

class Input
{
public:
	Input(void);
	virtual ~Input(void);

	bool isKeyHit(unsigned short key);
	void keyDown(unsigned short key);
	void keyUp(unsigned short key);

private:
	std::vector<bool> keys;
};


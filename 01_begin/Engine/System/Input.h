#pragma once

#include <Windows.h>
#include <vector>

class Input
{
public:
	Input(void);
	virtual ~Input(void);

	bool isKeyHit(unsigned char key);
	
	void keyDown(unsigned char key);
	void keyUp(unsigned char key);

private:
	std::vector<bool> keys;
};


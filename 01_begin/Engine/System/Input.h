#pragma once

#include <Windows.h>

class Input
{
public:
	Input(void);
	virtual ~Input(void);

	bool keyHit(short key);
};


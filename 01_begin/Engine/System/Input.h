#pragma once

#include "Window.h"

class Input
{
public:
	Input(void);
	virtual ~Input(void);

	bool keyHit(short key);
};


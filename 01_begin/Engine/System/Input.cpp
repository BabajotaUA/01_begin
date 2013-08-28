#include "Input.h"
#include <iostream>

Input::Input(void)
{
	keys = std::vector<bool>(256, false);
	std::cout << "Input CREATED\n" << std::endl;
}

Input::~Input(void)
{
	std::cout << "Input DELETED\n" << std::endl;
}



bool Input::isKeyHit(unsigned char key)
{
	return false;
}

void Input::keyDown(unsigned char key)
{
	keys[key] = true;
}

void Input::keyUp(unsigned char key)
{
	keys[key] = false;
}

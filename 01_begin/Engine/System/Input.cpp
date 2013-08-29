#include "Input.h"
#include <iostream>

Input::Input(void)
{
	keysDown = std::vector<bool>(256, false);
	keysHit = std::vector<bool>(256, false);
	std::cout << "Input CREATED\n" << std::endl;
}

Input::~Input(void)
{
	std::cout << "Input DELETED\n" << std::endl;
}

bool Input::isKeyHit(unsigned char key)
{
	bool result = keysHit[key];
	keysHit[key] = false;
	return result;
}

bool Input::isKeyDown(unsigned char scanCode)
{
	return keysDown[scanCode];
}

bool Input::isMouseDown(unsigned char scanCode)
{
	return false;
}

void Input::keyDown(unsigned char key)
{
	keysDown[key] = true;
	keysHit[key] = true;
}

void Input::keyUp(unsigned char key)
{
	keysDown[key] = false;
	keysHit[key] = false;
}

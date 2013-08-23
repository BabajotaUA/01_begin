#include "Input.h"

Input::Input(void)
{
}

Input::~Input(void)
{
}

bool Input::keyHit(short key)
{
	MSG systemInput;
	if(PeekMessage(&systemInput, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&systemInput);
        DispatchMessage(&systemInput);

        if(systemInput.message == WM_QUIT)
			return false;
    }
	return true;
}

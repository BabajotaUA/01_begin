#include "Engine\Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCommandLine, int nCommandShow)
{
	auto engine = Engine();

	engine.CreateGraphics3D(800, 600);
	engine.SetApplicationTitle(L"My APP");

	while(engine.isRunning())
    {
		if(engine.input.isKeyHit(VK_ESCAPE))
			break;

		engine.RenderWorld();
    }
	return 0;
}
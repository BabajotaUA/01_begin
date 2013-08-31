#include "Engine\Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPSTR lpCommandLine, int nCommandShow)
{
	auto engine = Engine();

    engine.graphics.createGraphics3D(1024,768);
	engine.graphics.setApplicationTitle(L"My APP");

    while(engine.isRunning())
    {
		if(engine.input.isKeyHit(VK_ESCAPE))
			break;

		engine.graphics.renderWorld();
    }
	return 0;
}
#include "Graphics.h"


Graphics::Graphics(void)
{
    graphicsWidth = graphicsHeight = 0;
}


Graphics::~Graphics(void)
{
}

void Graphics::setApplicationTitle(const LPCWSTR &title)
{
    graphicsWindow.setWindowTitle(title);
}

void Graphics::createGraphics3D(int screenWidth, int screenHeight, bool isFullScreen)
{
    setScreenResolution(screenWidth, screenHeight);
    graphicsWindow.createWindowRect(graphicsWidth, graphicsHeight, isFullScreen);
    graphicsD3D.D3DInitialisation(graphicsWindow.getWindowHandle(), graphicsWidth, graphicsHeight, isFullScreen);
	graphicsD3D.D3DSetRenderTarget();
	graphicsD3D.D3DSetViewport();
}

void Graphics::setScreenResolution(int width, int height)
{
	if (width == 0 || height == 0)
	{
		graphicsWidth = GetSystemMetrics(SM_CXSCREEN);
		graphicsHeight = GetSystemMetrics(SM_CYSCREEN);
	}
	else
	{
		graphicsWidth = width;
		graphicsHeight = height;
	}
}

void Graphics::renderWorld()
{
    graphicsD3D.D3DDraw();
}

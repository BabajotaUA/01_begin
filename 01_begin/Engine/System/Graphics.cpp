#include "Graphics.h"
#include <stdexcept>

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
	try
	{
		setScreenResolution(screenWidth, screenHeight);
		graphicsWindow.createWindowRect(graphicsWidth, graphicsHeight, isFullScreen);
		graphicsD3D.Initialisation(graphicsWindow.getWindowHandle(), graphicsWidth, graphicsHeight, isFullScreen);
	}
	catch (const std::invalid_argument &e)
	{
		MessageBox(graphicsWindow.getWindowHandle(), (LPCWSTR)(e.what()), L"sdfs",MB_OK);
	}
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

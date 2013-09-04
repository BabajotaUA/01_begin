#include "Graphics.h"
#include <exception>

Graphics::Graphics(void)
{
    graphicsWidth = graphicsHeight = 0;
    ok = true;
}

Graphics::~Graphics(void)
{
}

bool Graphics::isOK() const
{
    return ok;
}

void Graphics::showErrorMessage(const char* title, const std::exception &e)
{
    MessageBoxA(graphicsWindow.getWindowHandle(), e.what(), title, MB_OK | MB_ICONERROR);
    ok = false;
}

void Graphics::setApplicationTitle(const LPCWSTR &title)
{
    try
    {
        graphicsWindow.setWindowTitle(title);
    }
    catch (const std::exception &e)
    {
        showErrorMessage("ERROR: Window title wasn't seted!", e);
    }
}

void Graphics::createGraphics3D(int screenWidth, int screenHeight, bool isFullScreen)
{
	try
	{
		setScreenResolution(screenWidth, screenHeight);
		graphicsWindow.createWindowRect(graphicsWidth, graphicsHeight, isFullScreen);
		graphicsD3D.Initialisation(graphicsWindow.getWindowHandle(), graphicsWidth, graphicsHeight, isFullScreen);
        graphicsD3D.InitialisePipeline();
        createMatrices();
	}
    catch (const std::exception &e)
	{
        showErrorMessage("ERROR: Graphics wasn't initialisated!", e);
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

void Graphics::createMatrices()
{
	auto fieldOfView = XM_PI / 4.0f;
	auto screenAspect = (float)(graphicsWidth / graphicsHeight);
	projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, 0.001f, 1000.0f);
	worldMatrix = XMMatrixIdentity();
	ortoMatrix = XMMatrixOrthographicLH((FLOAT)graphicsWidth, (FLOAT)graphicsHeight, 0.001f, 1000.0f);
}

void Graphics::renderWorld()
{
    graphicsD3D.Draw();
}

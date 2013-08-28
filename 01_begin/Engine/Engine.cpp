#include "Engine.h"
#include <iostream>

Engine::Engine() : Window()
{
	graphicsBackBuffer = nullptr;
	graphicsContext = nullptr;
	graphicsDevice = nullptr;
	graphicsSwapChain = nullptr;
    std::cout << "Engine CREATED\n" << std::endl;
}

Engine::~Engine(void)
{
	graphicsSwapChain->SetFullscreenState(FALSE, NULL);
	graphicsSwapChain->Release();
	graphicsContext->Release();
	graphicsDevice->Release();
	graphicsBackBuffer->Release();
    std::cout << "Engine DELETED\n" << std::endl;
}

void Engine::CreateGraphics3D(int screenWidth, int screenHeight)
{
	setScreenResolution(screenWidth, screenHeight);
	D3DInitialisation();
	D3DSetRenderTarget();
	D3DSetViewport();
}

void Engine::setScreenResolution(int width, int height)
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

void Engine::D3DInitialisation()
{
	createWindowRect(graphicsWidth, graphicsHeight);

	DXGI_SWAP_CHAIN_DESC swapChainDescription;
    ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDescription.BufferCount = 1;
    swapChainDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDescription.BufferDesc.Width = graphicsWidth;
	swapChainDescription.BufferDesc.Height = graphicsHeight;
    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.OutputWindow = windowHandle();
    swapChainDescription.SampleDesc.Count = 4;
	swapChainDescription.Windowed = !FULL_SCREEN;
	swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL, NULL, NULL, NULL,
        D3D11_SDK_VERSION,
        &swapChainDescription,
        &graphicsSwapChain,
        &graphicsDevice, NULL,
        &graphicsContext);
}

void Engine::D3DSetRenderTarget()
{
	ID3D11Texture2D *pBackBuffer = nullptr;
    graphicsSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	graphicsDevice->CreateRenderTargetView(pBackBuffer, NULL, &graphicsBackBuffer);
    pBackBuffer->Release();

    graphicsContext->OMSetRenderTargets(1, &graphicsBackBuffer, NULL);
}

void Engine::D3DSetViewport()
{
	D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
	viewport.Width = graphicsWidth;
	viewport.Height = graphicsHeight;

	graphicsContext->RSSetViewports(1, &viewport);
}

void Engine::RenderWorld()
{
	graphicsContext->ClearRenderTargetView(graphicsBackBuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));
	graphicsSwapChain->Present(0, 0);
}
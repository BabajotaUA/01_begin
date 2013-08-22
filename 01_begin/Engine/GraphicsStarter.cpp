#include "GraphicsStarter.h"
#include <iostream>

GraphicsStarter::GraphicsStarter(HINSTANCE& hInstance, int windowNCommandShow) : Window(hInstance, windowNCommandShow)
{
	graphicsBackBuffer = nullptr;
	graphicsContext = nullptr;
	graphicsDevice = nullptr;
	graphicsSwapChain =nullptr;
    std::cout << "GraphicsStarter CREATED\n";
}


GraphicsStarter::~GraphicsStarter(void)
{
	graphicsSwapChain->SetFullscreenState(TRUE, NULL);
	graphicsSwapChain->Release();
	graphicsContext->Release();
	graphicsDevice->Release();
	graphicsBackBuffer->Release();
    std::cout << "GraphicsStarter DELETED\n";
}

void GraphicsStarter::CreateGraphics3D(int width, int height)
{
	graphicsWidth = width;
	graphicsHeight = height;

	this->D3DInitialisation();
	this->D3DSetRenderTarget();
	this->D3DSetViewport();
}

void GraphicsStarter::RenderWorld()
{
	graphicsContext->ClearRenderTargetView(graphicsBackBuffer, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f));
	graphicsSwapChain->Present(0, 0);
}

void GraphicsStarter::D3DInitialisation()
{
	DXGI_SWAP_CHAIN_DESC swapChainDescription;

    ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDescription.BufferCount = 1;
    swapChainDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDescription.BufferDesc.Width = graphicsWidth;
	swapChainDescription.BufferDesc.Height = graphicsHeight;
    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription.OutputWindow = CreateWindowRect(graphicsWidth, graphicsHeight);
    swapChainDescription.SampleDesc.Count = 4;
	swapChainDescription.Windowed = FALSE;
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

void GraphicsStarter::D3DSetRenderTarget()
{
	ID3D11Texture2D *pBackBuffer = nullptr;
    graphicsSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	graphicsDevice->CreateRenderTargetView(pBackBuffer, NULL, &graphicsBackBuffer);
    pBackBuffer->Release();

    graphicsContext->OMSetRenderTargets(1, &graphicsBackBuffer, NULL);
}

void GraphicsStarter::D3DSetViewport()
{
	D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
	viewport.Width = graphicsWidth;
	viewport.Height = graphicsHeight;

	graphicsContext->RSSetViewports(1, &viewport);
}

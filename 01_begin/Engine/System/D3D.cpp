#include "D3D.h"


D3D::D3D(void)
{
}


D3D::~D3D(void)
{
    graphicsSwapChain->SetFullscreenState(FALSE, NULL);
	graphicsSwapChain->Release();
	graphicsContext->Release();
	graphicsDevice->Release();
	graphicsBackBuffer->Release();
}

void D3D::getWindowSizeFromHWND(HWND hWnd)
{
    LPRECT currentWindowRect;
    /*if (GetWindowRect(hWnd, currentWindowRect))
    {
        screenWidth = (currentWindowRect->right - currentWindowRect->left);
        screenHeight = (currentWindowRect->bottom - currentWindowRect->top);
    }
    else
    {*/
        screenWidth = 400;
        screenHeight = 300;
    //}
}

void D3D::D3DInitialisation(HWND windowHandle, bool fullScreen)
{
    getWindowSizeFromHWND(windowHandle);
	DXGI_SWAP_CHAIN_DESC swapChainDescription;
    ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDescription.BufferCount = 1;
    swapChainDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDescription.BufferDesc.Width = screenWidth;
    swapChainDescription.BufferDesc.Height = screenHeight;
    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.OutputWindow = windowHandle;
    swapChainDescription.SampleDesc.Count = 4;
	swapChainDescription.Windowed = !fullScreen;
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

void D3D::D3DSetRenderTarget()
{
	ID3D11Texture2D *pBackBuffer = nullptr;
    graphicsSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	graphicsDevice->CreateRenderTargetView(pBackBuffer, NULL, &graphicsBackBuffer);
    pBackBuffer->Release();

    graphicsContext->OMSetRenderTargets(1, &graphicsBackBuffer, NULL);
}

void D3D::D3DSetViewport()
{
	D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = screenWidth;
    viewport.Height = screenHeight;

	graphicsContext->RSSetViewports(1, &viewport);
}

void D3D::D3DDraw()
{
	float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	graphicsContext->ClearRenderTargetView(graphicsBackBuffer, color);
	graphicsSwapChain->Present(0, 0);
}

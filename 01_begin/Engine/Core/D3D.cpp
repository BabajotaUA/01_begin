#include "D3D.h"
#include <stdexcept>

D3D::D3D(void) : D3DFactory()
{
    screenWidth = screenHeight = videoMemory = 0;
    d3dBackBuffer = nullptr;
    d3dContext = nullptr;
    d3dDevice = nullptr;
    d3dSwapChain = nullptr;
    d3dDepthStencilBuffer = nullptr;
    d3dDepthStencilState = nullptr;
    d3dDepthStencilView = nullptr;
    d3dRasterizerState = nullptr;
}

D3D::~D3D(void)
{
    d3dSwapChain->SetFullscreenState(FALSE, NULL);
	d3dSwapChain->Release();
	d3dContext->Release();
	d3dDevice->Release();
	d3dBackBuffer->Release();
    d3dDepthStencilBuffer->Release();
    d3dDepthStencilState->Release();
    d3dDepthStencilView->Release();
    d3dRasterizerState->Release();
}


ID3D11DeviceContext* D3D::getContext() const
{
    return d3dContext;
}

ID3D11Device* D3D::getDevice() const
{
    return d3dDevice;
}

IDXGISwapChain* D3D::getSwapChain() const
{
    return d3dSwapChain;
}

void D3D::D3DDraw()
{
    float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
    d3dContext->ClearRenderTargetView(d3dBackBuffer, color);
    d3dContext->ClearDepthStencilView(d3dDepthStencilView ,D3D11_CLEAR_DEPTH, 1.0f, 0);
	d3dSwapChain->Present(1, 0);
}


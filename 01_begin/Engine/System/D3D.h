#pragma once

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcommon.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

class D3D
{
public:
    D3D(void);
    virtual ~D3D(void);

    void D3DInitialisation(HWND windowHandle, bool fullScreen);
	void D3DSetRenderTarget();
	void D3DSetViewport();
    void D3DDraw();

private:
    int screenWidth, screenHeight;
    IDXGISwapChain* graphicsSwapChain;
    ID3D11Device* graphicsDevice;
    ID3D11DeviceContext* graphicsContext;
	ID3D11RenderTargetView* graphicsBackBuffer;

    void getWindowSizeFromHWND(HWND hWnd);
};


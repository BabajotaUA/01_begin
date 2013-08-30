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

    void D3DInitialisation(HWND windowHandle, int width, int height, bool fullScreen);
	void D3DSetRenderTarget();
	void D3DSetViewport();
    void D3DDraw();

private:
    int screenWidth, screenHeight, videoMemory;
    char videoAdapterDescription[128];
    IDXGISwapChain* d3dSwapChain;
    ID3D11Device* d3dDevice;
    ID3D11DeviceContext* d3dContext;
	ID3D11RenderTargetView* d3dBackBuffer;

    void D3DSetupDisplaySettings();
};


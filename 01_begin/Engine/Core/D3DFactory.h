#pragma once
#include <dxgi.h>
#include <d3d11.h>

class D3DFactory
{
public:
    D3DFactory(void);
    virtual ~D3DFactory(void);

    void Initialisation(HWND windowHandle, int width, int height, bool fullScreen);

protected:
    int screenWidth, screenHeight, videoMemory;
    char videoAdapterDescription[128];
    bool fullScreen;
    HWND windowHandle;
    IDXGISwapChain* d3dSwapChain;
    ID3D11Device* d3dDevice;
    ID3D11DeviceContext* d3dContext;
	ID3D11RenderTargetView* d3dBackBuffer;
    ID3D11Texture2D* d3dDepthStencilBuffer;
    ID3D11DepthStencilState* d3dDepthStencilState;
    ID3D11DepthStencilView* d3dDepthStencilView;
    ID3D11RasterizerState* d3dRasterizerState;

    DXGI_RATIONAL SetupDisplaySettings();
    void setRenderTarget();
	void setViewport();
    void createDevice();
    void createBackBuffer();
    void createDepthBuffer();
    void createDepthStencilState();
    void createDepthStencilView();
};


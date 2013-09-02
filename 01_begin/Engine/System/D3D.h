#pragma once

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <DirectXMath.h>

using namespace DirectX;

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

class D3D
{
public:
    D3D(void);
    virtual ~D3D(void);

    void Initialisation(HWND windowHandle, int width, int height, bool fullScreen);
    void D3DDraw();

private:
    int screenWidth, screenHeight, videoMemory;
    char videoAdapterDescription[128];
    bool fullScreen;
    IDXGISwapChain* d3dSwapChain;
    ID3D11Device* d3dDevice;
    ID3D11DeviceContext* d3dContext;
	ID3D11RenderTargetView* d3dBackBuffer;
    ID3D11Texture2D* d3dDepthStencilBuffer;
    ID3D11DepthStencilState* d3dDepthStencilState;
    ID3D11DepthStencilView* d3dDepthStencilView;
    ID3D11RasterizerState* d3dRasterizerState;
	XMMATRIX d3dProjectionMatrix;
	XMMATRIX d3dWorldMatrix;
	XMMATRIX d3dOrtoMatrix;

    DXGI_RATIONAL SetupDisplaySettings();
    void setRenderTarget();
	void setViewport();
    void createDevice(HWND hWnd);
    void createBackBuffer();
    void createDepthBuffer();
    void createDepthStencilState();
    void createDepthStencilView();
	void createMatrix();
};


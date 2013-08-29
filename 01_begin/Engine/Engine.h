#pragma once

#include "System\Window.h"
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <memory>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

class Engine : public Window
{
public:
    Engine();
    virtual ~Engine(void);

    void CreateGraphics3D(int screenWidth = 0, int screenHeight = 0);
	void RenderWorld();

private:
	int graphicsWidth, graphicsHeight;
    IDXGISwapChain* graphicsSwapChain;
    ID3D11Device* graphicsDevice;
    ID3D11DeviceContext* graphicsContext;
	ID3D11RenderTargetView* graphicsBackBuffer;

	void D3DInitialisation();
	void D3DSetRenderTarget();
	void D3DSetViewport();
	void setScreenResolution(int width, int height);
};


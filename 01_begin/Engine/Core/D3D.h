#pragma once

#include "D3DFactory.h"
#include <d3dcommon.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

class D3D : public D3DFactory
{
public:
    D3D(void);
    virtual ~D3D(void);
    
    void D3DDraw();

    IDXGISwapChain* getSwapChain() const;
    ID3D11Device* getDevice() const;
    ID3D11DeviceContext* getContext() const;
    ID3D11RenderTargetView* getBackBuffer() const;
    ID3D11DepthStencilView* getDepthStencilView() const;
};


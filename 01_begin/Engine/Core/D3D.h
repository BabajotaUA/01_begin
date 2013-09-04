#pragma once

#include "D3DFactory.h"
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")

class D3D : public D3DFactory
{
public:
    D3D(void);
    virtual ~D3D(void);

    void InitialisePipeline();
    void Draw();

    IDXGISwapChain* getSwapChain() const;
    ID3D11Device* getDevice() const;
    ID3D11DeviceContext* getContext() const;

private:
    
    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;
};


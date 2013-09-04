#include "D3DPipeline.h"
#include <exception>
#include <string>
#include <vector>

D3DPipeline::D3DPipeline(void) : D3DFactory()
{
    vertexShader = nullptr;
    pixelShader = nullptr;
}

D3DPipeline::~D3DPipeline(void)
{
    if(vertexShader)
        vertexShader->Release();
    if(pixelShader)
        pixelShader->Release();
}


ID3D11DeviceContext* D3DPipeline::getContext() const
{
    return d3dContext;
}

ID3D11Device* D3DPipeline::getDevice() const
{
    return d3dDevice;
}

IDXGISwapChain* D3DPipeline::getSwapChain() const
{
    return d3dSwapChain;
}

void D3DPipeline::InitialisePipeline()
{
    ID3D10Blob* errorMessage = nullptr;
	ID3D10Blob* vertexShaderBuffer = nullptr;
	ID3D10Blob* pixelShaderBuffer = nullptr;

    if(FAILED(D3DCompileFromFile(L"Engine/Shaders/VertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, &vertexShaderBuffer, &errorMessage)))
    {
        if(errorMessage)
        {
            auto txt = std::string("Compile Error in VertexShader.hlsl\n");
            txt.append((char*)errorMessage->GetBufferPointer());
            throw std::exception(txt.c_str());
        }
        else
            throw std::exception("Missing Shader File: VertexShader.hlsl");
    }

    if(FAILED(D3DCompileFromFile(L"Engine/Shaders/PixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, &pixelShaderBuffer, &errorMessage)))
    {
        if(errorMessage)
        {
            auto txt = std::string("Compile Error in PixelShader.hlsl\n");
            txt.append((char*)errorMessage->GetBufferPointer());
            throw std::exception(txt.c_str());
        }
        else
            throw std::exception("Missing Shader File: PixelShader.hlsl");
    }

    d3dDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);
    d3dDevice->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);

    vertexShaderBuffer->Release();
    pixelShaderBuffer->Release();

    d3dContext->VSSetShader(vertexShader, nullptr, 0);
    d3dContext->PSSetShader(pixelShader, nullptr, 0);
}

void D3DPipeline::Draw()
{
    std::vector<float> color(4, 0.2f);
    d3dContext->ClearRenderTargetView(d3dBackBuffer, color.data());
    d3dContext->ClearDepthStencilView(d3dDepthStencilView ,D3D11_CLEAR_DEPTH, 1.0f, 0);
	d3dSwapChain->Present(1, 0);
}


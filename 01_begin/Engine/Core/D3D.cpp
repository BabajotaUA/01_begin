#include "D3D.h"
#include <stdexcept>
#include <fstream>

D3D::D3D(void) : D3DFactory()
{
    vertexShader = nullptr;
    pixelShader = nullptr;
}

D3D::~D3D(void)
{
    if(vertexShader)
        vertexShader->Release();
    if(pixelShader)
        pixelShader->Release();
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

void D3D::InitialisePipeline()
{
    ID3D10Blob* errorMessage = nullptr;
	ID3D10Blob* vertexShaderBuffer = nullptr;
	ID3D10Blob* pixelShaderBuffer = nullptr;

    if(FAILED(D3DCompileFromFile(L"Engine/Shaders/VertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, &vertexShaderBuffer, &errorMessage)))
    {
        if(errorMessage)
        {
            generateErrorLog(errorMessage);
            throw std::exception("Compile Error in VertexShader.hlsl\nSee ERROR_LOG.txt");
        }
        else
            throw std::exception("Missing Shader File: VertexShader.hlsl");
    }

    if(FAILED(D3DCompileFromFile(L"Engine/Shaders/PixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, &pixelShaderBuffer, &errorMessage)))
    {
        if(errorMessage)
        {
            generateErrorLog(errorMessage);
            throw std::exception("Compile Error in PixelShader.hlsl\nSee ERROR_LOG.txt");
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

void D3D::generateErrorLog(ID3D10Blob* errorMessage)
{
	char* compileErrors;
	std::ofstream fout;

	// Get a pointer to the error message text buffer.
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message.
	auto bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
    fout.write(compileErrors, bufferSize);

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
}

void D3D::Draw()
{
    float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
    d3dContext->ClearRenderTargetView(d3dBackBuffer, color);
    d3dContext->ClearDepthStencilView(d3dDepthStencilView ,D3D11_CLEAR_DEPTH, 1.0f, 0);
	d3dSwapChain->Present(1, 0);
}


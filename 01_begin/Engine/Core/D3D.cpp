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

void D3D::InitalisePipeline()
{
    ID3D10Blob* errorMessage = nullptr;
	ID3D10Blob* vertexShaderBuffer = nullptr;
	ID3D10Blob* pixelShaderBuffer = nullptr;

    if(FAILED(D3DCompileFromFile(L"Engine/Shaders/VertexShader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, &vertexShaderBuffer, &errorMessage)))
    {
        if(errorMessage)
            outputShaderErrorMessage(errorMessage, windowHandle, L"VertexShader.hlsl");
        else
            MessageBox(windowHandle, L"VertexShader.hlsl", L"Missing Shader File", MB_OK);
        return;
    }
    else
        d3dDevice->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &vertexShader);

    if(FAILED(D3DCompileFromFile(L"Engine/Shaders/PixelShader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, &pixelShaderBuffer, &errorMessage)))
    {
        if(errorMessage)
            outputShaderErrorMessage(errorMessage, windowHandle, L"PixelShader.hlsl");
        else
            MessageBox(windowHandle, L"PixelShader.hlsl", L"Missing Shader File", MB_OK);
        return;
    }
    else
        d3dDevice->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &pixelShader);

    vertexShaderBuffer->Release();
    pixelShaderBuffer->Release();

    d3dContext->VSSetShader(vertexShader, nullptr, 0);
    d3dContext->PSSetShader(pixelShader, nullptr, 0);
}

void D3D::clearShaderFileBuffers()
{

}

void D3D::outputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
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
	for(int i=0; i<bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file.
	fout.close();

	// Release the error message.
	errorMessage->Release();
    errorMessage = nullptr;

	// Pop a message up on the screen to notify the user to check the text file for compile errors.
	MessageBox(hwnd, L"Error compiling shader.  Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

void D3D::Draw()
{
    float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
    d3dContext->ClearRenderTargetView(d3dBackBuffer, color);
    d3dContext->ClearDepthStencilView(d3dDepthStencilView ,D3D11_CLEAR_DEPTH, 1.0f, 0);
	d3dSwapChain->Present(1, 0);
}


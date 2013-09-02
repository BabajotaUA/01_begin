#include "D3D.h"
#include <stdexcept>

D3D::D3D(void)
{
    screenWidth = screenHeight = videoMemory = 0;
    d3dBackBuffer = nullptr;
    d3dContext = nullptr;
    d3dDevice = nullptr;
    d3dSwapChain = nullptr;
    d3dDepthStencilBuffer = nullptr;
    d3dDepthStencilState = nullptr;
    d3dDepthStencilView = nullptr;
    d3dRasterizerState = nullptr;
}


D3D::~D3D(void)
{
    d3dSwapChain->SetFullscreenState(FALSE, NULL);
	d3dSwapChain->Release();
	d3dContext->Release();
	d3dDevice->Release();
	d3dBackBuffer->Release();
    d3dDepthStencilBuffer->Release();
    d3dDepthStencilState->Release();
    d3dDepthStencilView->Release();
    d3dRasterizerState->Release();
}

DXGI_RATIONAL D3D::SetupDisplaySettings()
{
    unsigned int numModes = 0;
    IDXGIFactory* factory;
    IDXGIAdapter* adapter;
    IDXGIOutput* adapterOutput;
    DXGI_ADAPTER_DESC adapterDesc;
    DXGI_RATIONAL refreshRate;

    ZeroMemory(&refreshRate, sizeof(DXGI_RATIONAL));

    CreateDXGIFactory(__uuidof(IDXGIFactory),(void**)&factory);
    if(FAILED(factory->EnumAdapters(0,&adapter)))
		throw std::invalid_argument("");
    adapter->EnumOutputs(0,&adapterOutput);
    adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
    auto displayModeList = new DXGI_MODE_DESC[numModes];
    adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);

    for(int i=0; i<numModes; i++)
	{
		if(displayModeList[i].Width == (unsigned int)screenWidth)
		{
			if(displayModeList[i].Height == (unsigned int)screenHeight)
			{
                refreshRate = displayModeList[i].RefreshRate;
			}
		}
	}

    adapter->GetDesc(&adapterDesc);
    videoMemory = adapterDesc.DedicatedVideoMemory / 1024 / 1024;
    wcstombs(videoAdapterDescription, adapterDesc.Description, 128);

    delete [] displayModeList;
    adapterOutput->Release();
    adapter->Release();
    factory->Release();

    return refreshRate;
}

void D3D::Initialisation(HWND windowHandle, int width, int height, bool fullScreenVal)
{
    screenWidth = width; screenHeight = height;
    fullScreen = fullScreenVal;
    createDevice(windowHandle);
    setRenderTarget();
    setViewport();
}

void D3D::createDevice(HWND hWnd)
{
    auto featureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC swapChainDescription; 
    ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));    

    swapChainDescription.BufferCount = 1;
    swapChainDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDescription.BufferDesc.Width = screenWidth;
    swapChainDescription.BufferDesc.Height = screenHeight;
    swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription.BufferDesc.RefreshRate = SetupDisplaySettings();
	swapChainDescription.OutputWindow = hWnd;
    swapChainDescription.SampleDesc.Count = 4;
	swapChainDescription.Windowed = !fullScreen;
	swapChainDescription.Flags = 0;

    if(FAILED(
        D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL, 0, &featureLevel, 1,
        D3D11_SDK_VERSION,
        &swapChainDescription,
        &d3dSwapChain,
        &d3dDevice, NULL,
        &d3dContext)))
        throw std::invalid_argument("D3D11CreateDeviceAndSwapChain - FAIL");
}

void D3D::createBackBuffer()
{
    ID3D11Texture2D *pBackBuffer = nullptr;
    d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &d3dBackBuffer);
    pBackBuffer->Release();
}

void D3D::createDepthBuffer()
{
    D3D11_TEXTURE2D_DESC depthBufferDesc;
    ZeroMemory(&depthBufferDesc,sizeof(D3D11_TEXTURE2D_DESC));
    depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
    d3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &d3dDepthStencilBuffer);
}

void D3D::createDepthStencilState()
{
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
    depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	// Stencil operations if pixel is front-facing.
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	// Stencil operations if pixel is back-facing.
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
    d3dDevice->CreateDepthStencilState(&depthStencilDesc, &d3dDepthStencilState);
    d3dContext->OMSetDepthStencilState(d3dDepthStencilState, 1);
}

void D3D::createDepthStencilView()
{
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
    d3dDevice->CreateDepthStencilView(d3dDepthStencilBuffer, &depthStencilViewDesc, &d3dDepthStencilView);
}

void D3D::setRenderTarget()
{
    createBackBuffer();
    createDepthBuffer();
    createDepthStencilState();
    createDepthStencilView();
    d3dContext->OMSetRenderTargets(1, &d3dBackBuffer, d3dDepthStencilView);
}

void D3D::setViewport()
{
    D3D11_RASTERIZER_DESC rasterDesc;
    ZeroMemory(&rasterDesc, sizeof(D3D11_RASTERIZER_DESC));
    rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;
    d3dDevice->CreateRasterizerState(&rasterDesc, &d3dRasterizerState);

	D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = (float)screenWidth;
    viewport.Height = (float)screenHeight;

    d3dContext->RSSetState(d3dRasterizerState);
	d3dContext->RSSetViewports(1, &viewport);
}

void D3D::D3DDraw()
{
	float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	d3dContext->ClearRenderTargetView(d3dBackBuffer, color);
	d3dSwapChain->Present(1, 0);
}

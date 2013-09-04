#include "D3DFactory.h"
#include <exception>

D3DFactory::D3DFactory(void)
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


D3DFactory::~D3DFactory(void)
{
    if(d3dSwapChain)
    {
        d3dSwapChain->SetFullscreenState(FALSE, NULL);
        d3dSwapChain->Release();
    }
	if(d3dContext)
        d3dContext->Release();
    if(d3dDevice)
	    d3dDevice->Release();
    if(d3dBackBuffer)
	    d3dBackBuffer->Release();
    if(d3dDepthStencilBuffer)
        d3dDepthStencilBuffer->Release();
    if(d3dDepthStencilState)
        d3dDepthStencilState->Release();
    if(d3dDepthStencilView)
        d3dDepthStencilView->Release();
    if(d3dRasterizerState)
        d3dRasterizerState->Release();
}

void D3DFactory::Initialisation(HWND windowHandlePtr, int width, int height, bool fullScreenVal)
{
    windowHandle = windowHandlePtr;
    screenWidth = width; screenHeight = height;
    fullScreen = fullScreenVal;
    createDevice();
    setRenderTarget();
    setViewport();
}

DXGI_RATIONAL D3DFactory::SetupDisplaySettings()
{
    IDXGIFactory* factory;
    if(FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory),(void**)&factory)))
        throw std::exception("SetupDisplaySettings() - FAILED\nCreateDXGIFactory - FAILED");

    IDXGIAdapter* adapter;
    if(FAILED(factory->EnumAdapters(0,&adapter)))
        throw std::exception("SetupDisplaySettings() - FAILED\nEnumAdapters - FAILED");

    IDXGIOutput* adapterOutput;
    if(FAILED(adapter->EnumOutputs(0,&adapterOutput)))
        throw std::exception("SetupDisplaySettings() - FAILED\nEnumOutputs - FAILED");

    unsigned int numModes = 0;
    adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
    auto displayModeList = new DXGI_MODE_DESC[numModes];
    adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);

    DXGI_RATIONAL refreshRate;
    ZeroMemory(&refreshRate, sizeof(DXGI_RATIONAL));

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

    DXGI_ADAPTER_DESC adapterDesc;
    adapter->GetDesc(&adapterDesc);
    videoMemory = adapterDesc.DedicatedVideoMemory / 1024 / 1024;
    wcstombs(videoAdapterDescription, adapterDesc.Description, 128);

    delete [] displayModeList;
    adapterOutput->Release();
    adapter->Release();
    factory->Release();

    return refreshRate;
}

void D3DFactory::createDevice()
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
    swapChainDescription.OutputWindow = windowHandle;
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
        throw std::exception("createDevice() - FAILED");
}

void D3DFactory::createBackBuffer()
{
    ID3D11Texture2D *pBackBuffer = nullptr;
    d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if(FAILED(d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &d3dBackBuffer)))
        throw std::exception("createBackBuffer() - FAILED");

    pBackBuffer->Release();
}

void D3DFactory::createDepthBuffer()
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
    if(FAILED(d3dDevice->CreateTexture2D(&depthBufferDesc, NULL, &d3dDepthStencilBuffer)))
        throw std::exception("createDepthBuffer() - FAILED");
}

void D3DFactory::createDepthStencilState()
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
    if(FAILED(d3dDevice->CreateDepthStencilState(&depthStencilDesc, &d3dDepthStencilState)))
        throw std::exception("createDepthStencilState() - FAILED");
    d3dContext->OMSetDepthStencilState(d3dDepthStencilState, 1);
}

void D3DFactory::createDepthStencilView()
{
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
    ZeroMemory(&depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
    depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
    if(FAILED(d3dDevice->CreateDepthStencilView(d3dDepthStencilBuffer, &depthStencilViewDesc, &d3dDepthStencilView)))
        throw std::exception("createBackBuffer() - FAILED");
}

void D3DFactory::setRenderTarget()
{
    createBackBuffer();
    createDepthBuffer();
    createDepthStencilState();
    createDepthStencilView();
    d3dContext->OMSetRenderTargets(1, &d3dBackBuffer, d3dDepthStencilView);
}

void D3DFactory::setViewport()
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
    if(FAILED(d3dDevice->CreateRasterizerState(&rasterDesc, &d3dRasterizerState)))
        throw std::exception("setViewport() - FAILED\nCreateRasterizerState() - FAILED");

	D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = (float)screenWidth;
    viewport.Height = (float)screenHeight;

    d3dContext->RSSetState(d3dRasterizerState);
	d3dContext->RSSetViewports(1, &viewport);
}
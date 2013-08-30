#include "D3D.h"

D3D::D3D(void)
{
    screenWidth = screenHeight = videoMemory = 0;
    d3dBackBuffer = nullptr;
    d3dContext = nullptr;
    d3dDevice = nullptr;
    d3dSwapChain = nullptr;
}


D3D::~D3D(void)
{
    d3dSwapChain->SetFullscreenState(FALSE, NULL);
	d3dSwapChain->Release();
	d3dContext->Release();
	d3dDevice->Release();
	d3dBackBuffer->Release();
}

void D3D::D3DSetupDisplaySettings()
{
    unsigned int numModes, numerator, denominator;
    IDXGIFactory* factory;
    IDXGIAdapter* adapter;
    IDXGIOutput* adapterOutput;
    DXGI_ADAPTER_DESC adapterDesc;

    CreateDXGIFactory(__uuidof(IDXGIFactory),(void**)&factory);
    if(FAILED(factory->EnumAdapters(0,&adapter)))
        throw "";
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
				numerator = displayModeList[i].RefreshRate.Numerator;
				denominator = displayModeList[i].RefreshRate.Denominator;
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
}

void D3D::D3DInitialisation(HWND windowHandle, int width, int height, bool fullScreen)
{
    screenWidth = width; screenHeight = height;

    D3DSetupDisplaySettings();
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
	swapChainDescription.OutputWindow = windowHandle;
    swapChainDescription.SampleDesc.Count = 4;
    swapChainDescription.SampleDesc.Quality = 1;
	swapChainDescription.Windowed = !fullScreen;
	swapChainDescription.Flags = 0;//DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

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
        throw "";
}

void D3D::D3DSetRenderTarget()
{
	ID3D11Texture2D *pBackBuffer = nullptr;
    d3dSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &d3dBackBuffer);
    pBackBuffer->Release();

    d3dContext->OMSetRenderTargets(1, &d3dBackBuffer, NULL);
}

void D3D::D3DSetViewport()
{
	D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = screenWidth;
    viewport.Height = screenHeight;

	d3dContext->RSSetViewports(1, &viewport);
}

void D3D::D3DDraw()
{
	float color[4] = {0.0f, 0.2f, 0.4f, 1.0f};
	d3dContext->ClearRenderTargetView(d3dBackBuffer, color);
	d3dSwapChain->Present(0, 0);
}

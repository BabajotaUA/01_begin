#include "GraphicsStarter.h"


GraphicsStarter::GraphicsStarter(Window &parentWindow) : Window(parentWindow)
{
    std::cout << "GraphicsStarter CREATED\n";
}


GraphicsStarter::~GraphicsStarter(void)
{
    std::cout << "GraphicsStarter DELETED\n";
}

void GraphicsStarter::CreateGraphics3D(int width, int height)
{
    std::shared_ptr<DXGI_SWAP_CHAIN_DESC> swapChainDescription(new DXGI_SWAP_CHAIN_DESC());

    ZeroMemory(swapChainDescription.get(), sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDescription->BufferCount = 1;
    swapChainDescription->BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDescription->BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription->OutputWindow = CreateWindowRect(width, height);
    swapChainDescription->SampleDesc.Count = 4;
    swapChainDescription->Windowed = TRUE;

    D3D11CreateDeviceAndSwapChain(NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL, NULL, NULL, NULL,
        D3D11_SDK_VERSION,
        swapChainDescription.get(),
        &graphicsSwapChain,
        &graphicsDevice, NULL,
        &graphicsContext);

}

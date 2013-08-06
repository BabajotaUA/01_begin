#pragma once

#include "Window\Window.h"
#include <d3d11.h>
#include <iostream>
#include <memory>

#pragma comment (lib, "d3d11.lib")

class GraphicsStarter : public Window
{
public:
    GraphicsStarter(Window &parentWindow);
    virtual ~GraphicsStarter(void);

    void CreateGraphics3D(int width, int height);

private:
    std::shared_ptr<IDXGISwapChain> graphicsSwapChain;
    std::shared_ptr<ID3D11Device> graphicsDevice;
    std::shared_ptr<ID3D11DeviceContext> graphicsContext;
};


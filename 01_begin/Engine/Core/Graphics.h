#pragma once

#include "Window.h"
#include "D3D.h"

class Graphics
{
public:
    Graphics(void);
    virtual ~Graphics(void);

    void renderWorld();
    void createGraphics3D(int screenWidth = 0, int screenHeight = 0, bool fullScreen = false);
    void setApplicationTitle(const LPCWSTR &title);

private:
    int graphicsWidth, graphicsHeight;

    D3D graphicsD3D;
    Window graphicsWindow;

    void setScreenResolution(int width, int height);
};


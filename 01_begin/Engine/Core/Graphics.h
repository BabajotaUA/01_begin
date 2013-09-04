#pragma once

#include "Window.h"
#include "D3D.h"
#include <DirectXMath.h>

using namespace DirectX;

class Graphics
{
public:
    Graphics(void);
    virtual ~Graphics(void);

    void renderWorld();
    void createGraphics3D(int screenWidth = 0, int screenHeight = 0, bool fullScreen = false);
    void setApplicationTitle(const LPCWSTR &title);
    bool isOK() const;

private:
    bool ok;
    int graphicsWidth, graphicsHeight;

    D3D graphicsD3D;
    Window graphicsWindow;
    XMMATRIX projectionMatrix;
	XMMATRIX worldMatrix;
	XMMATRIX ortoMatrix;

    void setScreenResolution(int width, int height);
    void createMatrices();
};


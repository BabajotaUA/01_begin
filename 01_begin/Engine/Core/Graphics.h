#pragma once

#include "Window.h"
#include "D3DPipeline.h"
#include "../Assets/Mesh.h"
#include <DirectXMath.h>

using namespace DirectX;

class Graphics
{
public:
    Graphics(void);
    virtual ~Graphics(void);

    bool isOK() const;
    void renderWorld();
    void createGraphics3D(int screenWidth = 0, int screenHeight = 0, bool fullScreen = false);
    void setApplicationTitle(const LPCWSTR &title);

private:
    bool ok;
    int graphicsWidth, graphicsHeight;

    D3DPipeline graphicsD3D;
    Mesh mesh;
    Window graphicsWindow;
    XMMATRIX projectionMatrix;
	XMMATRIX worldMatrix;
	XMMATRIX ortoMatrix;

    void setScreenResolution(int width, int height);
    void createMatrices();
    void showErrorMessage(const char* title, const std::exception &e);
};


#pragma once

#include <d3d11.h>
#include <memory>
#include <DirectXMath.h>

struct Vertex
{
    float x, y, z;
    DirectX::XMFLOAT4 Color;
};

class Mesh
{
public:
    Mesh(void);
    virtual ~Mesh(void);

    int getIndexCount() const;

private:
    std::shared_ptr<ID3D11Buffer> vertexBuffer, indexBuffer;
    int indexCount;
};


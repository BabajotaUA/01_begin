#pragma once

#include <d3d11.h>
#include <memory>
#include <DirectXMath.h>
#include "Entity.h"

struct Vertex
{
    float x, y, z;
    DirectX::XMFLOAT4 Color;
};

class Mesh : public Entity
{
public:
    Mesh(void);
    virtual ~Mesh(void);

    int getIndexCount() const;
    
    void positionEntity(float x, float y, float z);
    void moveEntity(float x, float y, float z);
    void rotateEntity(float x, float y, float z);
    void scaleEntity(float x, float y, float z);
    void pointEntity(const Entity &observerEntity, const Entity &targetEntity);
    float entityDistance(const Entity &sourceEntity, const Entity &destinationEntity);
    void hideEntity();
    void showEntity();

private:
    std::shared_ptr<ID3D11Buffer> vertexBuffer, indexBuffer;
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 scale;
    DirectX::XMFLOAT3 rotation;
    bool visible;
    int indexCount;
};


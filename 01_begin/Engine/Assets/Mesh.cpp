#include "Mesh.h"

Mesh::Mesh(void)
{
    vertexBuffer = nullptr;
    indexBuffer = nullptr;
}

Mesh::~Mesh(void)
{
}

int Mesh::getIndexCount() const
{
    return indexCount;
}

void Mesh::moveEntity(float x, float y, float z)
{
    position.x += x;
    position.y += y;
    position.z += z;
}

void Mesh::positionEntity(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void Mesh::rotateEntity(float x, float y, float z)
{
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
}

void Mesh::scaleEntity(float x, float y, float z)
{
    scale.x *= x;
    scale.y *= y;
    scale.z *= z;
}

void Mesh::showEntity()
{
    visible = true;
}

void Mesh::hideEntity()
{
    visible = false;
}

float Mesh::entityDistance(const Entity &sourceEntity, const Entity &destinationEntity)
{
    return 0.0f;
}

void Mesh::pointEntity(const Entity &observerEntity, const Entity &targetEntity)
{
}
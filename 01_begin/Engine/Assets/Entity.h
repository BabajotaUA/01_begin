#pragma once
#include <DirectXMath.h>

class Entity
{
public:
    virtual ~Entity() {}

    virtual void positionEntity(float x, float y, float z) = 0;
    virtual void moveEntity(float x, float y, float z) = 0;
    virtual void rotateEntity(float x, float y, float z) = 0;
    virtual void scaleEntity(float x, float y, float z) = 0;
    virtual void pointEntity(const Entity &observerEntity, const Entity &targetEntity) = 0;
    virtual float entityDistance(const Entity &sourceEntity, const Entity &destinationEntity) = 0;
    virtual void hideEntity() = 0;
    virtual void showEntity() = 0;
    
};
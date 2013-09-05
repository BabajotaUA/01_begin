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

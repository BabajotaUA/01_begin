#pragma once

#include "Core\Graphics.h"
#include "Core\Input.h"
#include <memory>

class Engine
{
public:
    Engine(void);
    virtual ~Engine(void);

    bool isRunning();

    Graphics graphics;
    Input input;
};


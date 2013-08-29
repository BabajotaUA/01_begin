#pragma once

#include "System\Graphics.h"
#include "System\Input.h"
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


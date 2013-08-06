#include "GraphicsStarter.h"


GraphicsStarter::GraphicsStarter(Window &parentWindow) : Window(parentWindow)
{
    std::cout << "GraphicsStarter CREATED\n";
}


GraphicsStarter::~GraphicsStarter(void)
{
    std::cout << "GraphicsStarter DELETED\n";
}

void GraphicsStarter::CreateGraphics3D(int width, int height)
{
    CreateWindowRect(width, height);
}

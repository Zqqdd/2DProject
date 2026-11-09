#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <iostream>

#include "Window.h"

int main()
{
    Window window;
    if(!window.create())
    {
        std::cerr << "Failed to create window!" << std::endl;
        return 1;
    }
    
    return 0;
}
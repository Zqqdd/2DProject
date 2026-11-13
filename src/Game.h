#pragma once 
#include <SDL3/SDL.h>
#include "Window.h"

class Game
{
    public : 
    Game() = default;
    ~Game() = default;

    bool run();

    Window window;
    
    SDL_Window* windowptr;


    private : 


};
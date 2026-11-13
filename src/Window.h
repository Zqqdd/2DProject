#pragma once

#include <SDL3/SDL.h>

class Window
{
    public:
        Window() = default;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        ~Window();

        bool create();
        void destroy();

        SDL_Window* GetAddress();
    
    
    private:

        SDL_GLContext context = nullptr;
        SDL_Window *window = nullptr;

};
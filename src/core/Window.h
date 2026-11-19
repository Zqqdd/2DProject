#pragma once

#include <SDL3/SDL.h>

class Window
{
    public:
        Window() = default;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        ~Window();

        bool create(); // Renvoie false en cas d'échec
        void destroy();

        SDL_Window* GetAddress();
    
    
    private:
        SDL_GLContext context = nullptr; // Le contexte OpenGL attaché à cette fenêtre
        SDL_Window *window = nullptr;

};
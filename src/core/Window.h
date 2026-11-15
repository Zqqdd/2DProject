// Window : la fenêtre SDL et son contexte OpenGL, et rien d'autre.
#pragma once

#include <SDL3/SDL.h>

class Window
{
    public:
        Window() = default;
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        ~Window();

        bool create(); // Initialise SDL, crée la fenêtre puis le contexte OpenGL. Renvoie false si échec.
        void destroy();

        SDL_Window* GetAddress(); // Donne l'adresse de la fenêtre SDL brute, pour les fonctions SDL qui la demandent.
    
    
    private:
        SDL_GLContext context = nullptr; // Le contexte OpenGL attaché à cette fenêtre.
        SDL_Window *window = nullptr;

};
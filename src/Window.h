// Window : la fenêtre SDL et son contexte OpenGL, et rien d'autre.
#pragma once

#include <SDL3/SDL.h>

class Window
{
    public:
        Window() = default;
        // Copie interdite : deux Window pointant vers la même fenêtre SDL la détruiraient deux fois.
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        // Le destructeur appelle destroy() : la fenêtre se ferme toute seule en fin de vie (principe RAII).
        ~Window();

        // Initialise SDL, crée la fenêtre puis le contexte OpenGL. Renvoie false au premier échec.
        bool create();
        void destroy();

        // Donne la fenêtre SDL brute, pour les fonctions SDL qui la demandent.
        SDL_Window* GetAddress();
    
    
    private:

        // Le contexte OpenGL : l'état d'OpenGL (textures, réglages) attaché à cette fenêtre.
        // Tant qu'il n'existe pas, aucun appel gl... ne fonctionne.
        SDL_GLContext context = nullptr;
        SDL_Window *window = nullptr;

};
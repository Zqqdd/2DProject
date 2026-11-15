// Game : le chef d'orchestre. Il crée la fenêtre, fait tourner la boucle de jeu
// et appelle les autres modules (Renderer aujourd'hui, World plus tard).
#pragma once 
#include <SDL3/SDL.h>
#include "Window.h"

class Game
{
    public : 
    Game() = default;
    ~Game() = default;

    // Lance le jeu. Renvoie false si l'initialisation échoue.
    bool run();

    // La fenêtre appartient au jeu : elle est détruite automatiquement avec lui.
    Window window;
    
    // Raccourci vers la fenêtre SDL brute, rempli au début de run().
    SDL_Window* windowptr = nullptr;


    private : 


};
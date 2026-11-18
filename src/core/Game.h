// Game : le chef d'orchestre. Il crée la fenêtre, fait tourner la boucle de jeu
// et appelle les autres modules
#pragma once 
#include <SDL3/SDL.h>
#include "Window.h"
#include "../render/Renderer.h"
#include "../ui/MenuManager.h"

enum class GameState {MainMenu, Playing, Paused};

class Game
{
    public : 
    Game() = default;
    ~Game() = default;

    bool run(); // Lance le jeu. Renvoie false si l'initialisation échoue.

    Window window; // La fenêtre appartient au jeu, elle est détruite automatiquement avec lui.
    Renderer renderer;
    MenuManager menuManager;

    SDL_Window* windowptr = nullptr; // Adresse vers la fenêtre SDL brute, remplie au début de run().


    private :
    GameState state = GameState::MainMenu;
};
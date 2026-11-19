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

    bool run(); // Lance le jeu.

    Window window;
    SDL_Window* windowptr = nullptr; // Adresse vers la fenêtre SDL.
    
    Renderer renderer;
    MenuManager menuManager;


    private :
    GameState state = GameState::MainMenu;
};
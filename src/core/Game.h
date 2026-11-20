#pragma once 

#include <SDL3/SDL.h>

#include "Window.h"
#include "../render/Renderer.h"
#include "../ui/MenuManager.h"
#include "GameScene.h"

enum class GameState { InMenu, Playing };

struct FrameInfo
{
    int width = 0;
    int height = 0;
    float mouseX = 0.0f;
    float mouseY = 0.0f;
    bool mouseDown = false;
    float deltaTime = 0.0f; // Temps entre les frames
};

class Game
{
    public : 

        bool run(); // Lance le jeu

    private :

        bool init();
        void readFrameInfo();
        void handleEvents();
        void update();
        void draw();
        void shutdown();
        void changeState(GameState newState);

        Window window;
        SDL_Window* windowptr = nullptr; // Adresse vers la fenêtre SDL

        Renderer renderer;
        MenuManager menuManager;
        GameScene gameScene;

        GameState state = GameState::InMenu;
        FrameInfo frame;
        bool running = true;
};
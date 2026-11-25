#include "Game.h"
#include "../Player.h"

#include "../render/Renderer.h"

#include "iostream"

bool Game::run()
{
    if(!init()) return false;

    while(running) // Boucle du jeu
    {
        readFrameInfo();
        handleEvents();
        update();
        draw();
    }
    shutdown();
    return true;
}

bool Game::init()
{
    if(!window.create()) // Initialisation de la fenètre
    {
        std::cerr << "Failed to create the window!" << std::endl;
        return false;
    }
    windowptr = window.GetAddress();

    menuManager.load(renderer);
    lastTicks = SDL_GetTicks();
    return true;
}

void Game::readFrameInfo()
{
    SDL_GetWindowSizeInPixels(windowptr, &frame.width, &frame.height);
    SDL_MouseButtonFlags mouseButtons = SDL_GetMouseState(&frame.mouseX, &frame.mouseY);
    frame.mouseDown = (mouseButtons & SDL_BUTTON_LMASK) != 0;
    Uint64 now = SDL_GetTicks();
    frame.deltaTime = (now - lastTicks) / 1000.0f;
    lastTicks = now;
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) // File d'évènement
    {
        if(event.type == SDL_EVENT_QUIT) running = false;
        gameScene.handleEvent(event);
    }
    if(frame.mouseDown && menuManager.handleClick(frame.mouseX, frame.mouseY, frame.width, frame.height) == MenuRequest::Quit) running = false;
    if(frame.mouseDown && menuManager.handleClick(frame.mouseX, frame.mouseY, frame.width, frame.height) == MenuRequest::StartGame) changeState(GameState::Playing);
}

void Game::update()
{
    switch (state)
    {
    case GameState::InMenu:
        menuManager.update(frame.mouseX, frame.mouseY, frame.mouseDown, frame.width, frame.height);
        break;
    case GameState::Playing:
        gameScene.update(frame.deltaTime);
        break;
    }
}

void Game::draw()
{
    renderer.beginFrame(frame.width, frame.height); // Prépare l'écran pour l'affichage

    switch (state)
    {
    case GameState::InMenu:
        menuManager.draw(renderer, frame.width, frame.height);
        break;
    case GameState::Playing:
        gameScene.draw(renderer, frame.width, frame.height);
        break;
    }

    SDL_GL_SwapWindow(windowptr); // Affiche la nouvelle frame
}

void Game::shutdown()
{
    menuManager.unload(renderer);
    gameScene.unload();
}

void Game::changeState(GameState newState)
{
    if(newState == state) return;

    if(newState == GameState::InMenu)
    {
        gameScene.unload();
    }
    if(newState == GameState::Playing)
    {
        gameScene.load(renderer);
    }

    state = newState;
}
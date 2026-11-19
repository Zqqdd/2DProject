#include "Game.h"
#include "../Player.h"

#include "../render/Renderer.h"

#include "iostream"

bool Game::run()
{
    if(!window.create()) // Initialisation de la fenètre
    {
        std::cerr << "Failed to create the window!" << std::endl;
        return false;
    }
    windowptr = window.GetAddress();

    ///////////////////////////////////////////////////////// LOAD
    menuManager.load(renderer);
    //----------------------------------------------------//

    bool running = true;
    while(running) // Boucle du jeu
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) // File d'évènement
        {
            if(event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        int width = 0;
        int height = 0;
        SDL_GetWindowSizeInPixels(windowptr, &width, &height);

        float mouseX = 0.0f;
        float mouseY = 0.0f;
        SDL_MouseButtonFlags mouseButtons = SDL_GetMouseState(&mouseX, &mouseY);
        bool mouseDown = (mouseButtons & SDL_BUTTON_LMASK) != 0;

        //////////////////////////////////////////////////////// UPDATE
        if(mouseDown && menuManager.handleClick(mouseX, mouseY, width, height) == MenuRequest::Quit)
            running = false;

        menuManager.update(mouseX, mouseY, mouseDown, width, height);
        
        renderer.beginFrame(width, height); // Prépare l'écran pour l'affichage
        //----------------------------------------------------//



        //////////////////////////////////////////////////////// DISPLAY
        menuManager.draw(renderer, width, height);

        SDL_GL_SwapWindow(windowptr); // Affiche la nouvelle frame
        //----------------------------------------------------//
    }
    return true;
}

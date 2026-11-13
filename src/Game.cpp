#include "Game.h"
#include <SDL3/SDL_opengl.h>
#include "iostream"

bool Game::run()
{
    if(!window.create())
    {
        std::cerr << "Failed to create the window!" << std::endl;
        return false;
    }

    bool running = true;

    windowptr = window.GetAddress();

    while(running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)
            {
                running = false;
            }
        }

        int width = 0;
        int height = 0;
        SDL_GetWindowSizeInPixels(windowptr, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(windowptr);
    }
    return true;
}

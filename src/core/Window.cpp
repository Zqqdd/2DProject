#include "Window.h"

#include <SDL3/SDL_opengl.h>
#include <iostream>

Window::~Window()
{
    Window::destroy();
}

bool Window::create()
{
    destroy(); // Permet de rappeler create() sans fuite : on repart d'un état propre.
    
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL failed to initiate! " << SDL_GetError() << std::endl;
        return false;
    }

    int version = SDL_GetVersion();
    std::cout << "SDL Initiated; Version: "
              << SDL_VERSIONNUM_MAJOR(version) << "."
              << SDL_VERSIONNUM_MINOR(version) << "."
              << SDL_VERSIONNUM_MICRO(version) << std::endl;

    
    window = SDL_CreateWindow("Sylven Project",
                                          1280, 720,
                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if(window == nullptr)
    {
        std::cerr << "SDL failed to create window! " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    std::cout << "SDL window created successfully!" << std::endl;

    context = SDL_GL_CreateContext(window); // Création du contexte OpenGL

    if(context == nullptr)
    {
        std::cerr << "SDL failed to create OpenGL context! " << SDL_GetError() << std::endl;
        // On défait ce qui a déjà été créé, dans l'ordre inverse.
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    std::cout << "SDL OpenGL context created successfully!" << std::endl;

    if(!SDL_GL_SetSwapInterval(1)) // Essaie d'activer la VSync
    {
        std::cerr << "SDL failed to set VSync! " << SDL_GetError() << std::endl;
    }

    const char *glVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION)); // Récupère la version d'OpenGL
    const char *glRenderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER)); // Récupère le nom de la carte graphique
    const char *glVendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR)); // Récupère le nom du fabricant de la carte graphique

    std::cout << "OpenGL Version: " << glVersion << std::endl;
    std::cout << "OpenGL Renderer: " << glRenderer << " by " << glVendor << std::endl;

    return true;
}

void Window::destroy()
{
    // Ordre inverse de la création : le contexte, puis la fenêtre, puis SDL.
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

SDL_Window* Window::GetAddress()
{
    return window;
}

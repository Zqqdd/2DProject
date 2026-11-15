#include "Window.h"

#include <SDL3/SDL_opengl.h>
#include <iostream>

Window::~Window()
{
    Window::destroy();
}

bool Window::create()
{
    // Permet de rappeler create() sans fuite : on repart d'un état propre.
    destroy();
    
    // SDL_Init passe avant tout autre appel SDL. VIDEO suffit pour une fenêtre et ses événements.
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

    
    // SDL_WINDOW_OPENGL est obligatoire pour pouvoir créer un contexte OpenGL sur cette fenêtre.
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

    // Le contexte se crée après la fenêtre et devient le contexte courant : à partir d'ici, les appels gl... marchent.
    context = SDL_GL_CreateContext(window);

    if(context == nullptr)
    {
        std::cerr << "SDL failed to create OpenGL context! " << SDL_GetError() << std::endl;
        // On défait ce qui a déjà été créé, dans l'ordre inverse.
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    std::cout << "SDL OpenGL context created successfully!" << std::endl;

    // VSync : 1 = attendre le rafraîchissement de l'écran. Evite le déchirement d'image et limite les FPS.
    // Un échec n'est pas bloquant, d'où l'absence de return false.
    if(!SDL_GL_SetSwapInterval(1))
    {
        std::cerr << "SDL failed to set VSync! " << SDL_GetError() << std::endl;
    }

    // glGetString renvoie des const GLubyte* : le cast sert uniquement à les afficher comme du texte.
    const char *glVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    const char *glRenderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    const char *glVendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));

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

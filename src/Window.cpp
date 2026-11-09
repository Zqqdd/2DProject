#include "Window.h"

#include <SDL3/SDL_opengl.h>
#include <iostream>

Window::~Window()
{
    Window::destroy();
}

bool Window::create()
{
    destroy();
    
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

    context = SDL_GL_CreateContext(window);

    if(context == nullptr)
    {
        std::cerr << "SDL failed to create OpenGL context! " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    std::cout << "SDL OpenGL context created successfully!" << std::endl;

    if(!SDL_GL_SetSwapInterval(1))
    {
        std::cerr << "SDL failed to set VSync! " << SDL_GetError() << std::endl;
    }

    const char *glVersion = reinterpret_cast<const char *>(glGetString(GL_VERSION));
    const char *glRenderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));
    const char *glVendor = reinterpret_cast<const char *>(glGetString(GL_VENDOR));

    std::cout << "OpenGL Version: " << glVersion << std::endl;
    std::cout << "OpenGL Renderer: " << glRenderer << " by " << glVendor << std::endl;

    bool running = true;

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
        SDL_GetWindowSizeInPixels(window, &width, &height);
        glViewport(0, 0, width, height);

        glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }
    return true;
}

void Window::destroy()
{
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
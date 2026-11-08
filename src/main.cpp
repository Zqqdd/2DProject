#include <SDL3/SDL.h>
#include <iostream>

int main()
{
    int version = SDL_GetVersion();
    std::cout << "SDL version : "
              << SDL_VERSIONNUM_MAJOR(version) << "."
              << SDL_VERSIONNUM_MINOR(version) << "."
              << SDL_VERSIONNUM_MICRO(version) << std::endl;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init a echoue : " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "SDL_Init OK" << std::endl;
    std::cin.get();

    SDL_Quit();
    return 0;
}
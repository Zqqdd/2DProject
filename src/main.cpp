#include <iostream>

#include "Game.h"

int main()
{
    Game game;
    if(!game.run())
    {
        std::cerr << "Failed to run the game!" << std::endl;
        return 1;
    }
    return 0;
}
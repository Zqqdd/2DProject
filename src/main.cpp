// Point d'entrée du programme.
// main se contente de créer le jeu et de le lancer : toute la logique est dans Game.
#include <iostream>

#include "Game.h"

int main()
{
    Game game;
    // run() contient la boucle de jeu : il ne rend la main qu'à la fermeture.
    if(!game.run())
    {
        std::cerr << "Failed to run the game!" << std::endl;
        // Un code de retour différent de 0 signale une erreur au système.
        return 1;
    }
    return 0;
}
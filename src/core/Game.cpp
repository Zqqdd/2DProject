#include "Game.h"
#include "../Player.h"

#include "../render/Renderer.h"

#include "iostream"

bool Game::run()
{
    // 1. Initialisation. Sans fenêtre, pas de contexte OpenGL, donc rien d'autre ne peut marcher.
    if(!window.create())
    {
        std::cerr << "Failed to create the window!" << std::endl;
        return false;
    }
    windowptr = window.GetAddress();


    // Le Renderer s'utilise après window.create() : charger une texture demande un contexte OpenGL.
    Renderer renderer;
    Texture texture = renderer.loadTexture("assets/textures/blocks/test.png"); // TEST


    // 2. Boucle de jeu. Un tour = une image (frame) : événements, dessin, affichage.
    bool running = true;
    while(running)
    {
        // On vide la file d'événements : SDL y range tout ce qui s'est passé depuis la frame précédente.
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

        // La taille est relue à chaque frame car la fenêtre est redimensionnable.
        // "InPixels" : la taille réelle en pixels, qui peut différer de la taille logique sur un écran haute densité.
        int width = 0;
        int height = 0;
        SDL_GetWindowSizeInPixels(windowptr, &width, &height);
        // Efface l'écran et prépare la projection. Tout ce qui se dessine vient après.
        renderer.beginFrame(width, height);
        // Coin haut gauche du dessin à (100, 500). Le x4 agrandit le pixel art pour qu'il soit visible.
        renderer.drawTexture(texture, 100.0f, 500.0f, texture.width*4.0f, texture.height*4.0f); //TEST

        // Double buffer : on a dessiné sur une image cachée, on l'échange avec celle affichée.
        // Avec la VSync, cet appel attend le rafraîchissement de l'écran (environ 60 fois par seconde).
        SDL_GL_SwapWindow(windowptr);
    }
    renderer.destroyTexture(texture); //TEST
    return true;
}

// Renderer : le seul module qui parle à OpenGL. Le reste du jeu passe par lui.
#pragma once

struct Texture // Toutes les propriétés d'une texture dont on a besoin
{
    unsigned int id = 0; // unsigned int = GLuint. 0 signifie "aucune texture".

    int width = 0; // Taille de l'image en pixels (pas sa taille à l'écran).
    int height = 0;
};

class Renderer
{
    public:
        Renderer() = default;
        ~Renderer() = default;

        Texture loadTexture(const char* filePath); // Charge un PNG et l'envoie à la carte graphique. En cas d'échec, renvoie une Texture dont id vaut 0.
        void destroyTexture(Texture& texture); // Libère la texture côté carte graphique et remet la structure à zéro.

        void beginFrame(int width, int height); // A appeler une fois au début de chaque frame, avec la taille de la fenêtre en pixels.

        // Dessine la texture dans un rectangle. xPos, yPos : son coin haut gauche, en pixels depuis le coin haut gauche de la fenêtre.
        void drawTexture(const Texture& texture, float xPos, float yPos, float textureDrawWidth, float textureDrawHeight);

    private:
};
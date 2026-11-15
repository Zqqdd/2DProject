// Renderer : le seul module qui parle à OpenGL. Le reste du jeu passe par lui.
#pragma once

// Une texture vue par le reste du jeu : le numéro donné par OpenGL et la taille de l'image.
struct Texture
{
    // unsigned int = GLuint. 0 signifie "aucune texture".
    unsigned int id = 0;
    // Taille de l'image en pixels (pas sa taille à l'écran).
    int width = 0;
    int height = 0;
};

class Renderer
{
    public:
        Renderer() = default;
        ~Renderer() = default;

        // Charge un PNG et l'envoie à la carte graphique. En cas d'échec, renvoie une Texture dont id vaut 0.
        Texture loadTexture(const char* filePath);
        // Libère la texture côté carte graphique et remet la structure à zéro.
        void destroyTexture(Texture& texture);

        // A appeler une fois au début de chaque frame, avec la taille de la fenêtre en pixels.
        void beginFrame(int width, int height);

        /* Dessine la texture dans un rectangle. xPos, yPos : son coin haut gauche, en pixels depuis
        le coin haut gauche de la fenêtre. textureDraw... : sa taille à l'écran. */
        void drawTexture(const Texture& texture, float xPos, float yPos, float textureDrawWidth, float textureDrawHeight);

    private:
};
// Renderer : le seul module qui parle à OpenGL. Le reste du jeu passe par lui.
#pragma once

struct Texture
{
    unsigned int id = 0; // 0 signifie "Aucune texture".

    int width = 0;
    int height = 0;
};

class Renderer
{
    public:
        Renderer() = default;
        ~Renderer() = default;

        Texture loadTexture(const char* filePath);
        void destroyTexture(Texture& texture);
        void drawTexture(const Texture& texture, float xPos, float yPos, float textureDrawWidth, float textureDrawHeight);

        void beginFrame(int width, int height); // A appeler une fois au début de chaque frame, avec la taille de la fenêtre en pixels.

    private:
};
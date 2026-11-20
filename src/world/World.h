#pragma once

#include "../render/Renderer.h"

class World
{
    public:

        bool init(Renderer& renderer, unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, int seed);
        void coordsToScreen(int x, int y, int z, float& screenX, float& screenY);

        bool getSize(int &x, int &y, int &z);
        bool getSeed(int &s);

        // Pas encore implémentés : ils affichent seulement un message.
        bool save();
        bool load();

        bool draw(Renderer& renderer);

        const int BLOCK_PX_SIZE = 32;

    private:

        bool setSize(int x, int y, int z);
        bool setSeed(int s);

        bool generate();

        int width = 0; // x
        int depth = 0; // y
        int height = 0; // z

        int seed = 0;

        const char* blockPath = "assets/textures/blocks/grass.png";
        Texture blockTexture;
};
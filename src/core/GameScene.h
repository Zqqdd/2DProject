#pragma once

#include "../world/World.h"

class GameScene
{
    public:

        void load(Renderer& renderer);
        void unload();

        void update();
        void draw(Renderer& renderer);

        World world;

    private:
};
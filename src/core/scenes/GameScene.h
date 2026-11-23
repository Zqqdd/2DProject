#pragma once

#include "world/World.h"
#include "render/Camera.h"

class GameScene
{
    public:

        void load(Renderer& renderer);
        void unload();

        void update(float deltaTime);
        void updateCamera(float deltaTime, const bool* keys);
        void draw(Renderer& renderer, int windowWidth, int windowHeight);

        World world;
        Camera camera;

    private:
};
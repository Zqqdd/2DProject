#pragma once

#include "world/World.h"
#include "render/Camera.h"

#include <SDL3/SDL.h>

class GameScene
{
    public:

        void load(Renderer& renderer);
        void unload();

        void update(float deltaTime);
        void updateCamera(float deltaTime, const bool* keys);

        void draw(Renderer& renderer, int windowWidth, int windowHeight);
        void handleEvent(const SDL_Event& event);

        World world;
        Camera camera;

    private:
};
#include "GameScene.h"

#include <iostream>
#include <SDL3/SDL.h>

void GameScene::load(Renderer& renderer)
{
    if(!world.init(renderer, 10, 10, 1, 0))
    {
        std::cout << "Failed to init the world : ";
        return;
    }
}

void GameScene::unload()
{

}

void GameScene::update(float deltaTime)
{
    const bool* keys = SDL_GetKeyboardState(nullptr);

    updateCamera(deltaTime, keys);
}

void GameScene::updateCamera(float deltaTime, const bool* keys)
{
    float dirX = 0.0f;
    float dirY = 0.0f;
    if(keys[SDL_SCANCODE_D]) dirX += 1.0f;
    if(keys[SDL_SCANCODE_A]) dirX -= 1.0f;
    if(keys[SDL_SCANCODE_S]) dirY += 1.0f;
    if(keys[SDL_SCANCODE_W]) dirY -= 1.0f;

    float length = std::sqrt(dirX * dirX + dirY * dirY); // Normalisation pour éviter l'effet de vitesse du double input
    if (length > 0.0f)
    {
        dirX /= length;
        dirY /= length;
    }

    float worldDX = dirX * 0.5f + dirY;
    float worldDY = -dirX * 0.5f + dirY;

    camera.move(worldDX, worldDY, deltaTime);
}

void GameScene::draw(Renderer& renderer, int windowWidth, int windowHeight)
{
    world.draw(renderer, camera, windowWidth, windowHeight);
}
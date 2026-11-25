#include "GameScene.h"

#include <iostream>
#include <cmath>

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

void GameScene::handleEvent(const SDL_Event& event)
{
    if(event.type == SDL_EVENT_MOUSE_WHEEL)
    {
        float wheelY = event.wheel.y;

        if(event.wheel.direction == SDL_MOUSEWHEEL_FLIPPED) // Pour les trackpads qui inversent le sens de molette
            wheelY = -wheelY;
        
        if(wheelY > 0)
            camera.setZoom(camera.getZoom() + 1);
        
        if(wheelY < 0)
            camera.setZoom(camera.getZoom() - 1);
        
    }
}
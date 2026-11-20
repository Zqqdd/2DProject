#include "GameScene.h"

#include <iostream>

void GameScene::load(Renderer& renderer)
{
    if(!world.init(renderer, 8, 8, 1, 0))
    {
        std::cout << "Failed to init the world : ";
        return;
    }
}

void GameScene::unload()
{

}

void GameScene::update()
{

}

void GameScene::draw(Renderer& renderer)
{
    world.draw(renderer);
}
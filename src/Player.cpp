#include "Player.h"
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_opengl.h>
#include "render/Renderer.h"
#include "core/Game.h"




void Player::create()
{
    int PV = 10;
    int endurance = 5;
    int agility = 3;
    int force = 1;

}
void Player::kill()
{
    PV = 0;
}
void Player::heal()
{
    PV = 10;
}
void Player::attacked()
{
    PV -= 1;
}

void spawn(Renderer& renderer, float startX, float startY);
void draw(Renderer& renderer);

void Player::update(const bool* clavier, float dt)
{
    if (clavier[SDL_SCANCODE_A])
    {
        std::cout << "Q pressed succefully! " << std::endl;
    }
    if (clavier[SDL_SCANCODE_D])
    {
        std::cout << "D pressed succefully! " << std::endl;
    }
}
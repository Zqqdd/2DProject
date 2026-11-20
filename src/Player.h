#pragma once

#include "render/Renderer.h"

class Player 
{
    public :
        Player() = default;
        ~Player() = default;
        
        int PV; 
        int endurance;
        int force;
        int agility;

        void create();
        void kill();
        void heal();
        void attacked();

        void spawn();
        void update(const bool* clavier, float dt);
        void draw();

        Texture texture;

    private :
};
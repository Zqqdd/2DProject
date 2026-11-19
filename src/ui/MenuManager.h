#pragma once

#include "../render/Renderer.h"
#include "menus/MainMenu.h"

enum class MenuId {Main};
enum class MenuRequest {None, StartGame, Quit};

class MenuManager
{
    public:
        void load(Renderer& renderer);
        void unload(Renderer& renderer);
        MenuRequest handleClick(float mouseX, float mouseY, int windowWidth, int windowHeight);
        void draw(Renderer& renderer, int windowWidth, int windowHeight);
        void update(float mouseX, float mouseY, bool mouseDown, int windowWidth, int windowHeight);

    private:
        MenuId current = MenuId::Main;
        MainMenu mainMenu;
};
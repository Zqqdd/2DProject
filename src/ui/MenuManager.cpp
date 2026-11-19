#include "MenuManager.h"

void MenuManager::load(Renderer& renderer)
{
    mainMenu.load(renderer);
}

void MenuManager::unload(Renderer& renderer)
{
    mainMenu.unload(renderer);
}

MenuRequest MenuManager::handleClick(float mouseX, float mouseY, int windowWidth, int windowHeight)
{
    switch (current)
    {
        case MenuId::Main:
        {
            MainMenuResult result = mainMenu.handleClick(mouseX, mouseY, windowWidth, windowHeight);

            if(result == MainMenuResult::Play) return MenuRequest::StartGame;
            if(result == MainMenuResult::Quit) return MenuRequest::Quit;
            break;
        }
    }
    return MenuRequest::None;
}

void MenuManager::draw(Renderer& renderer, int windowWidth, int windowHeight)
{
    switch(current)
    {
    case MenuId::Main:
        mainMenu.draw(renderer, windowWidth, windowHeight);
        break;
    }
}

void MenuManager::update(float mouseX, float mouseY, bool mouseDown, int windowWidth, int windowHeight)
{
    switch(current)
    {
    case MenuId::Main:
        mainMenu.update(mouseX, mouseY, mouseDown, windowWidth, windowHeight);
        break;
    }
}
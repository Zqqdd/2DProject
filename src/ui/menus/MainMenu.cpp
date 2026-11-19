#include "MainMenu.h"

#include "../UIFunctions.h"

void MainMenu::load(Renderer& renderer)
{
    background = renderer.loadTexture("assets/textures/ui/menus/mainMenu/background.png");

    play.texturePath = "assets/textures/ui/menus/mainMenu/play.png";
    play.hoveredPath = "assets/textures/ui/menus/mainMenu/play_hover.png";
    play.pressedPath = "assets/textures/ui/menus/mainMenu/play_pressed.png";

    settings.texturePath = "assets/textures/ui/menus/mainMenu/settings.png";
    settings.hoveredPath = "assets/textures/ui/menus/mainMenu/settings_hover.png";
    settings.pressedPath = "assets/textures/ui/menus/mainMenu/settings_pressed.png";

    quit.texturePath = "assets/textures/ui/menus/mainMenu/quit.png";
    quit.hoveredPath = "assets/textures/ui/menus/mainMenu/quit_hover.png";
    quit.pressedPath = "assets/textures/ui/menus/mainMenu/quit_pressed.png";

    play.centerY = 0.45f;
    settings.centerY = 0.60f;
    quit.centerY = 0.75f;

    loadButton(renderer, play);
    loadButton(renderer, settings);
    loadButton(renderer, quit);

    buttons.push_back(play);
    buttons.push_back(settings);
    buttons.push_back(quit);
}

void MainMenu::unload(Renderer& renderer)
{
    renderer.destroyTexture(background);
    unloadButton(renderer, play);
    unloadButton(renderer, settings);
    unloadButton(renderer, quit);
}

MainMenuResult MainMenu::handleClick(float mouseX, float mouseY, int windowWidth, int windowHeight)
{
    if(isUnderMouse(play, mouseX, mouseY, windowWidth, windowHeight)) return MainMenuResult::Play;
    if(isUnderMouse(settings, mouseX, mouseY, windowWidth, windowHeight)) return MainMenuResult::Settings;
    if(isUnderMouse(quit, mouseX, mouseY, windowWidth, windowHeight)) return MainMenuResult::Quit;

    return MainMenuResult::None;
}

void MainMenu::draw(Renderer& renderer, int windowWidth, int windowHeight)
{
    drawBackground(renderer, background, windowWidth, windowHeight);
    drawButton(renderer, play, windowWidth, windowHeight);
    drawButton(renderer, settings, windowWidth, windowHeight);
    drawButton(renderer, quit, windowWidth, windowHeight);
}

void MainMenu::update(float mouseX, float mouseY, bool mouseDown, int windowWidth, int windowHeight)
{
    updateButton(play, mouseX, mouseY, mouseDown, windowWidth, windowHeight);
    updateButton(settings, mouseX, mouseY, mouseDown, windowWidth, windowHeight);
    updateButton(quit, mouseX, mouseY, mouseDown, windowWidth, windowHeight);
}
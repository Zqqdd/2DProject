#pragma once

#include "../../render/Renderer.h"
#include "../Button.h"

#include <vector>

enum class MainMenuResult {None, Play, Settings, Quit};

class MainMenu
{
    public:
        void load(Renderer& renderer);
        void unload(Renderer& renderer);
        MainMenuResult handleClick(float mouseX, float mouseY, int windowWidth, int windowHeight);
        void draw(Renderer& renderer, int windowWidth, int windowHeight);

    private:
        MainMenuResult result;

        std::vector<Button> buttons;

        Texture background;
        Button play;
        Button settings;
        Button quit;
};
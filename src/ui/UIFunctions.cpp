#include "UIFunctions.h"

#include <algorithm>
#include <cmath>

constexpr int UI_REFERENCE_HEIGHT = 180;

void loadButton(Renderer& renderer, Button& button)
{
    if(button.texturePath != nullptr)
    {
        button.texture = renderer.loadTexture(button.texturePath);
    }
}

void unloadButton(Renderer& renderer, Button& button)
{
    renderer.destroyTexture(button.texture);
}

Rect buttonRect(const Button& button, int windowWidth, int windowHeight)
{
    int scale = std::max(1, windowHeight / UI_REFERENCE_HEIGHT);

    Rect rect;
    rect.width = static_cast<float>(button.texture.width * scale);
    rect.height = static_cast<float>(button.texture.height * scale);

    rect.x = std::round(button.centerX * windowWidth - rect.width / 2.0f);
    rect.y = std::round(button.centerY * windowHeight - rect.height / 2.0f);
    return rect;
}

void drawBackground(Renderer& renderer, const Texture& background, int windowWidth, int windowHeight)
{
    if(background.id == 0)
    {
        return;
    }

    float scaleX = static_cast<float>(windowWidth) / background.width;
    float scaleY = static_cast<float>(windowHeight) / background.height;
    float scale = std::max(scaleX, scaleY);

    float drawWidth = background.width * scale;
    float drawHeight = background.height * scale;
    float x = (windowWidth - drawWidth) / 2.0f;
    float y = (windowHeight - drawHeight) / 2.0f;

    renderer.drawTexture(background, x, y, drawWidth, drawHeight);
}

void drawButton(Renderer& renderer, const Button& button, int windowWidth, int windowHeight)
{
    if(button.texture.id == 0)
    {
        return;
    }

    Rect rect = buttonRect(button, windowWidth, windowHeight);
    renderer.drawTexture(button.texture, rect.x, rect.y, rect.width, rect.height);
}

bool isUnderMouse(Button& button, float mouseX, float mouseY, int windowWidth, int windowHeight)
{
    if(buttonRect(button, windowWidth, windowHeight).contains(mouseX, mouseY))
    {
        return true;
    }
    return false;
}
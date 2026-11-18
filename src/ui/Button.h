#pragma once

#include "../render/Renderer.h"

enum class Action{None, Clicked, Hovered};

struct Button
{
    const char* texturePath = nullptr;
    float centerX = 0.5f;
    float centerY = 0.5f;
    Action action = Action::None;
    Texture texture;
};
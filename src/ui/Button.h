#pragma once

#include "../render/Renderer.h"

enum class State{Idle, Hovered, Pressed};

struct Button
{
    const char* texturePath = nullptr;
    const char* hoveredPath = nullptr;
    const char* pressedPath = nullptr;

    float centerX = 0.5f;
    float centerY = 0.5f;

    State state = State::Idle;

    Texture texture;
    Texture hoveredTexture;
    Texture pressedTexture;
};
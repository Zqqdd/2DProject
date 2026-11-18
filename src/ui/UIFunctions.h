#pragma once

#include "../render/Renderer.h"
#include "Button.h"
#include "Rect.h"

void loadButton(Renderer& renderer, Button& button);
void unloadButton(Renderer& renderer, Button& button);

Rect buttonRect(const Button& button, int windowWidth, int windowHeight);
void drawBackground(Renderer& renderer, const Texture& background, int windowWidth, int windowHeight);
void drawButton(Renderer& renderer, const Button& button, int windowWidth, int windowHeight);

bool isUnderMouse(Button& button, float mouseX, float mouseY, int windowWidth, int windowHeight);
#pragma once

struct Rect
{
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    bool contains(float px, float py)
    {
        return px >= x && px <= x + width && py >= y && py <= y + height;
    }
};

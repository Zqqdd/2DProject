#pragma once

class Camera
{
    public:

        void move(float dirX, float dirY, float deltaTime);
        void setZoom(int newZoom);
        int getZoom();
        void worldToScreen(float wx, float wy, float wz, int windowWidth, int windowHeight, float& sx, float& sy);
        void setPosition(float newX, float newY);
    private:

        float x = 0.0f; // Coordonnées dans le monde
        float y = 0.0f;
        int zoom = 4;
        float speed = 8.0f;
};
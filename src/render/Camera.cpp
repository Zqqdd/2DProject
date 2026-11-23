#include "Camera.h"

#include <cmath>

void Camera::move(float dirX, float dirY, float deltaTime)
{
    x += dirX * speed * deltaTime;
    y += dirY * speed * deltaTime;
}

void Camera::setZoom(int newZoom)
{
    zoom = newZoom;
}

int Camera::getZoom()
{
    return zoom;
}

void Camera::worldToScreen(float wx, float wy, float wz, int windowWidth, int windowHeight, float& sx, float& sy)
{
    float camIsoX = std::round((x - y) * 16.0f);
    float camIsoY = std::round((x + y) * 8.0f);

    float isoX = (wx - wy) * 16.0f;
    float isoY = (wx + wy) * 8.0f - wz * 16.0f;

    sx = (isoX - camIsoX) * zoom + windowWidth / 2.0f;
    sy = (isoY - camIsoY) * zoom + windowHeight / 2.0f;
}

void Camera::setPosition(float newX, float newY)
{
    x = newX;
    y = newY;
}
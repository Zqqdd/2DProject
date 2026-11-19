#include "Renderer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <iostream>

Texture Renderer::loadTexture(const char* filePath)
{
    Texture texture;

    SDL_Surface* surface = SDL_LoadPNG(filePath);  // Lire le fichier : les pixels arrivent en mémoire vive (RAM)
    if(!surface)
    {
        std::cerr << "Failed to load : " << filePath << ": " << SDL_GetError() << std::endl;
        return texture;
    }

    SDL_Surface* rgbaTexture = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32); // Convertir au format R, G, B, A

    SDL_DestroySurface(surface); // La surface d'origine ne sert plus donc destroy
    if(rgbaTexture == nullptr)
    {
        std::cerr << "Failed to convert " << filePath << ": " << SDL_GetError() << std::endl;
        return texture;
    }

    // Demander un numéro de texture à OpenGL, puis la rendre "courante"
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Copie des pixels de la RAM vers la carte graphique (VRAM)
    // Premier GL_RGBA : format de stockage. Second GL_RGBA + GL_UNSIGNED_BYTE : format des données
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rgbaTexture->w, rgbaTexture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaTexture->pixels);

    texture.width = rgbaTexture->w;
    texture.height = rgbaTexture->h;

    SDL_DestroySurface(rgbaTexture); // Libère la RAM
    return texture;
}

void Renderer::destroyTexture(Texture& texture)
{
    glDeleteTextures(1, &texture.id);
    texture = Texture{}; // Remet id à 0 dans l'objet texture
}

void Renderer::beginFrame(int width, int height)
{
    glViewport(0, 0, width, height); // Zone de dessin : toute la fenêtre.

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f); // Efface l'image précédente avec la couleur du ciel.
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    // Retour sur MODELVIEW (futur déplacement de la caméra), pour ne pas modifier la projection par erreur.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D); // Active les modules OpenGL souhaités.
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Réglages de transparence.
}

void Renderer::drawTexture(const Texture& texture, float xPos, float yPos, float textureDrawWidth, float textureDrawHeight)
{
    if(texture.id == 0) // Si id = 0 : le chargement a échoué. Mieux vaut ne rien dessiner qu'un rectangle blanc.
    {
        std::cerr << "Attempted to draw an uninitialized texture!" << std::endl;
        return;
    }

    glBindTexture(GL_TEXTURE_2D, texture.id);
    glColor3f(1.0f, 1.0f, 1.0f); // La couleur courante multiplie la texture : blanc = aucune teinte.

    // Un rectangle = 4 sommets, en faisant le tour : haut gauche, haut droite, bas droite, bas gauche.
    // glTexCoord2f (quel coin de l'image, de 0 à 1) précède toujours le glVertex2f auquel il s'applique.
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(xPos, yPos);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(xPos + textureDrawWidth, yPos);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(xPos + textureDrawWidth, yPos + textureDrawHeight);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(xPos, yPos + textureDrawHeight);
    glEnd();
}
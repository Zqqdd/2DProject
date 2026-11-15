#include "Renderer.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <iostream>

Texture Renderer::loadTexture(const char* filePath)
{
    // id = 0 par défaut : c'est cette texture "vide" qu'on renvoie en cas d'échec.
    Texture texture;

    // 1. Lire le fichier : les pixels arrivent en mémoire vive (RAM).
    SDL_Surface* surface = SDL_LoadPNG(filePath);
    if(!surface)
    {
        std::cerr << "Failed to load : " << filePath << ": " << SDL_GetError() << std::endl;
        return texture;
    }

    // 2. Imposer l'ordre R, G, B, A sur 1 octet chacun : c'est ce qu'on promet à glTexImage2D plus bas.
    SDL_Surface* rgbaTexture = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_RGBA32);

    // La surface d'origine ne sert plus, que la conversion ait réussi ou non. Donc destroy.
    SDL_DestroySurface(surface);
    if(rgbaTexture == nullptr)
    {
        std::cerr << "Failed to convert " << filePath << ": " << SDL_GetError() << std::endl;
        return texture;
    }

    // 3. Demander un numéro de texture à OpenGL, puis la rendre "courante" :
    // les appels suivants s'appliquent à elle.
    glGenTextures(1, &texture.id);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    // NEAREST = pas de lissage, le pixel art reste net.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // 4. Copier les pixels de la RAM vers la carte graphique (VRAM).
    // Premier GL_RGBA : format de stockage. Second GL_RGBA + GL_UNSIGNED_BYTE : format de nos données.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, rgbaTexture->w, rgbaTexture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaTexture->pixels);

    texture.width = rgbaTexture->w;
    texture.height = rgbaTexture->h;

    // 5. OpenGL a sa propre copie : celle en RAM peut être libérée.
    SDL_DestroySurface(rgbaTexture);
    return texture;
}

void Renderer::destroyTexture(Texture& texture)
{
    glDeleteTextures(1, &texture.id);
    // Remet id à 0 : la structure ne désigne plus une texture qui n'existe plus.
    texture = Texture{};
}

void Renderer::beginFrame(int width, int height)
{
    // Zone de dessin : toute la fenêtre.
    glViewport(0, 0, width, height);

    // Efface l'image précédente avec la couleur du ciel.
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Projection : nos coordonnées sont des pixels, (0,0) en haut à gauche, y vers le bas.
    // glLoadIdentity d'abord, car glOrtho se cumule avec la matrice existante au lieu de la remplacer.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    // Retour sur MODELVIEW (futur déplacement de la caméra), pour ne pas modifier la projection par erreur.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Ces réglages restent actifs jusqu'à ce qu'on les éteigne.
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    // Transparence : le pixel dessiné est mélangé avec le fond selon son alpha.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::drawTexture(const Texture& texture, float xPos, float yPos, float textureDrawWidth, float textureDrawHeight)
{
    // id = 0 : le chargement a échoué. Mieux vaut ne rien dessiner qu'un rectangle blanc.
    if(texture.id == 0)
    {
        std::cerr << "Attempted to draw an uninitialized texture!" << std::endl;
        return;
    }

    glBindTexture(GL_TEXTURE_2D, texture.id);
    // La couleur courante multiplie la texture : blanc = aucune teinte.
    glColor3f(1.0f, 1.0f, 1.0f);

    // Un rectangle = 4 sommets, en faisant le tour : haut gauche, haut droite, bas droite, bas gauche.
    // glTexCoord2f (quel coin de l'image, de 0 à 1) précède toujours le glVertex2f auquel il s'applique.
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(xPos, yPos);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(xPos + textureDrawWidth, yPos);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(xPos + textureDrawWidth, yPos + textureDrawHeight);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(xPos, yPos + textureDrawHeight);
    glEnd();
}
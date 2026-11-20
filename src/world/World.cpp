#include "World.h"

#include <iostream>

bool World::init(Renderer& renderer, unsigned int sizeX, unsigned int sizeY, unsigned int sizeZ, int seed)
{
    if(!setSize(sizeX, sizeY, sizeZ))
    {
        std::cout << "Failed to set the world size!" << std::endl;
        return false;
    }
    if(!setSeed(seed))
    {
        std::cout << "Failed to set the world seed!" << std::endl;
        return false;
    }

    blockTexture = renderer.loadTexture(blockPath);

    if(!generate())
    {
        std::cout << "Failed to generate the world!" << std::endl;
        return false;
    }
    return true;
}

void World::coordsToScreen(int x, int y, int z, float& screenX, float& screenY)
{
    screenX = (x-y)*(BLOCK_PX_SIZE/2);
    screenY = (x+y)*(BLOCK_PX_SIZE/4) - (z*(BLOCK_PX_SIZE/2));
}

bool World::setSize(int x, int y, int z)
{
    // Un monde vide ou de taille négative n'a pas de sens : on refuse.
    if (x <= 0 || y <= 0 || z <= 0)
    {
        std::cout << "Invalid size parameters! (How did you do that??)" << std::endl;
        return false;
    }

    width = x;
    depth = y;
    height = z;

    std::cout << "World size set to " << width << "x" << depth << "x" << height << std::endl;

    return true;
}

bool World::getSize(int &x, int &y, int &z)
{
    x = width;
    y = depth;
    z = height;
    return true;
}

bool World::setSeed(int s)
{
    seed = s;

    std::cout << "World seed set to " << seed << std::endl;

    return true;
}

bool World::getSeed(int &s)
{
    s = seed;
    return true;
}

bool World::save()
{
    std::cout << "Saving world..." << std::endl;
    
    return true;
}

bool World::load()
{
    std::cout << "Loading world..." << std::endl;
    
    return true;
}

// Version de test : affiche le monde dans la console, couche par couche (y = la hauteur).
// A remplacer par la vraie génération quand les blocs existeront.
bool World::generate()
{
    std::cout << "Generating world of size " << width << "x" << depth << "x" << height << " (XxYxZ)" << " with seed " << seed << std::endl;
    for (int z = 0; z < height; ++z)
    {
        std::cout << "Layer " << z + 1 << ":\n";
        for (int y = 0; y < depth; ++y)
        {
            for (int x = 0; x < width; ++x) 
            {
                std::cout << '*';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
    return true;
}

bool World::draw(Renderer& renderer)
{
    for (int z = 0; z < height; ++z)
    {
        for (int y = 0; y < depth; ++y)
        {
            for (int x = 0; x < width; ++x) 
            {
                float screenX;
                float screenY;
                coordsToScreen(x, y, z, screenX, screenY);
                renderer.drawTexture(blockTexture, screenX, screenY, blockTexture.width, blockTexture.height);
            }
        }
    }
    return true;
}
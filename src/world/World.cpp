#include "World.h"

#include <iostream>

bool World::setSize(int x, int y, int z)
{
    // Un monde vide ou de taille négative n'a pas de sens : on refuse.
    if (x <= 0 || y <= 0 || z <= 0)
    {
        std::cout << "Invalid size parameters!" << std::endl;
        return false;
    }

    width = x;
    height = y;
    depth = z;

    std::cout << "World size set to " << width << "x" << height << "x" << depth << std::endl;

    return true;
}

bool World::getSize(int &x, int &y, int &z)
{
    x = width;
    y = height;
    z = depth;
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
    std::cout << "Generating world of size " << width << "x" << height << "x" << depth << " with seed " << seed << std::endl;
    for (int y = 0; y < height; ++y)
    {
        std::cout << "Layer " << y + 1 << ":\n";
        for (int z = 0; z < depth; ++z)
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
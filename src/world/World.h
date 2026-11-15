// World : les données du monde (taille, seed, plus tard les blocs). Aucun affichage ici.
#pragma once

class World
{
    public:
        World() = default;
        ~World() = default;

        // Dimensions en blocs. Refuse les valeurs nulles ou négatives.
        bool setSize(int x, int y, int z);
        // Les getters remplissent les variables passées par référence.
        bool getSize(int &x, int &y, int &z);

        // La seed : le nombre de départ de la génération. Même seed = même monde.
        bool setSeed(int s);
        bool getSeed(int &s);

        // Pas encore implémentés : ils affichent seulement un message.
        bool save();
        bool load();

        bool generate();

    private:
        int width = 0; // x
        int height = 0; // y
        int depth = 0; // z

        int seed = 0;
};
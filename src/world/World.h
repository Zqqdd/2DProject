#pragma once

class World
{
    public:
        World() = default;
        ~World() = default;

        bool setSize(int x, int y, int z);
        bool getSize(int &x, int &y, int &z);

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
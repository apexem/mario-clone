#ifndef MARIO_H_INCLUDED
#define MARIO_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "entity.h"
#include "cTexture.h"
#include "defines.h"
#include "enemy.h"

class mario :public entity
{
    public:
        mario();

        void renderMario(SDL_Renderer* renderer, int camX, int camY);
        void input(SDL_Event& e);

        float getPosX();
        float getPosY();
        std::string getCoins();

        int getState();
        int collision(std::vector<entity*>& entities, std::vector<enemy> &enemies);
        void move(std::vector<entity*>& entities, std::vector<enemy> &enemies, float timePassed);

    private:

        int coinsObtained;
        int doubleJump;
        int collisionIndex;
        int animationIndex;
        int state;

        bool direction;

        int velX, velY;
        std::string *animPaths;
};

#endif // MARIO_H_INCLUDED

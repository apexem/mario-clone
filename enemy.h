#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "entity.h"
#include "cTexture.h"
#include "defines.h"

class enemy :public entity
{
public:
    enemy();
    enemy(float x, float y, int movingRangeL, int movingRangeR, std::string path);
    void render(SDL_Renderer* renderer, int camX, int camY);
    void move(float timePassed);

private:
    int velX;
    int movingRangeRight, movingRangeLeft;
    bool direction;
};

#endif // ENEMY_H_INCLUDED

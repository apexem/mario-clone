#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include "cTexture.h"
#include <string>
#include <cmath>

class entity
{
    public:
        entity();
        entity(float x, float y, std::string path);

        int getType();
        void render(SDL_Renderer* renderer, int camX, int camY);

        SDL_Rect getHitbox();
        int checkCollision(SDL_Rect hitbox);

    protected:
        SDL_Rect collider;
        float posX, posY;

        int entityType;

        std::string texturePath;
};


#endif // ENTITY_H_INCLUDED

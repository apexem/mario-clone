#include "entity.h"

entity::entity()
{
    posX=0;
    posY=0;
}

entity::entity(float x, float y, std::string path)
{
    posX = x;
    posY = y;

    entityType = 0;
    texturePath = path;

    if(texturePath == "obstacles/coin.jpg")
        entityType = 1;
    if(texturePath == "obstacles/spike.jpg")
        entityType = 2;

}

void entity::render(SDL_Renderer* renderer, int camX, int camY)
{
    cTexture texture;
    texture.loadFromFile(texturePath.c_str(), renderer);
    texture.render(posX - camX, posY - camY, renderer);

    collider.h = texture.getHeight();
    collider.w = texture.getWidth();

    texture.free();

    collider.x = posX;
    collider.y = posY;
}

SDL_Rect entity::getHitbox()
{
    SDL_Rect hitbox;

    hitbox.x = collider.x;
    hitbox.y = collider.y;
    hitbox.w = collider.w;
    hitbox.h = collider.h;

    return hitbox;
}

int entity:: getType()
{
    return entityType;
}

int entity::checkCollision(SDL_Rect hitbox)
{

    float w = 0.5 * (collider.w + hitbox.w);
    float h = 0.5 * (collider.h + hitbox.h);
    float dx = collider.x - hitbox.x;
    float dy = collider.y - hitbox.y;

    if(std::abs(dx) <= w && std::abs(dy) <= h)
    {
        float wy = w * dy;
        float hx = h * dx;

        if(wy > hx)
        {
            if(wy > -hx)
                return 1; // collision at the top
            else
                return 3; // collision on the left
        }
        else
        {
            if(wy > -hx)
                return 2; // collision on the right
            else
                return 4; // collision at the bottom
        }
    }
    return 0; // no collision
}

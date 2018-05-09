#include "enemy.h"

enemy::enemy()
{
    posX = 0;
    posY = 0;
    velX = 0;
}

enemy::enemy(float x, float y, int movingRangeL, int movingRangeR, std::string path)
{
    posX = x;
    posY = y;

    if(path == "goomba.png")
        velX = 300;
    else
        velX = 200;

    movingRangeRight = movingRangeR;
    movingRangeLeft = movingRangeL;

    direction = true;

    texturePath = path;
}
void enemy::render(SDL_Renderer* renderer, int camX, int camY)
{
    if(!direction)
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
    else
    {
        cTexture texture;
        texture.loadFromFile(texturePath.c_str(), renderer);
        texture.renderMirrored(posX - camX, posY - camY, renderer);

        collider.h = texture.getHeight();
        collider.w = texture.getWidth();

        texture.free();

        collider.x = posX;
        collider.y = posY;
    }
}
void enemy::move(float timePassed)
{
    if(direction)
        posX += velX * timePassed;
    else
        posX -= velX * timePassed;

    collider.x = posX;

    if(posX > movingRangeRight)
        direction = false;
    if(posX < movingRangeLeft)
        direction = true;
}

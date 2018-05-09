#include "mario.h"

mario::mario()
{
    posX = 20;
    posY = 850;

    velX = 0;
    velY = 0;

    texturePath = "mario/mario.bmp";

    coinsObtained = 0;
    doubleJump = 0;
    direction = true;
    state = 0;
    collisionIndex = 0;
    animationIndex = 0;

    animPaths = new std::string[4];
    animPaths[0] = "mario/mario_move0.bmp";
    animPaths[1] = "mario/mario_move1.bmp";
    animPaths[2] = "mario/mario_move2.bmp";
    animPaths[3] = "mario/mario_jump.bmp";
}

void mario::input(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_SPACE:
                if(doubleJump < 2)
                {
                    velY = -300;
                    doubleJump += 1;
                }
            break;
            case SDLK_ESCAPE:
                posX = 4;
                posY = 710;
            break;
            case SDLK_s: std::cout << collisionIndex << std::endl;
            break;
            case SDLK_a: velX = -180;
            break;
            case SDLK_d: velX = 180;
            break;
            case SDLK_q: posY -= 10;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_SPACE:
            {
                if(velY < - 150)
                    velY = - 150;
            }
            break;
            case SDLK_s:
            break;
            case SDLK_a: velX = 0;
            break;
            case SDLK_d: velX = 0;
            break;
        }
    }
}

int mario::collision(std::vector<entity*> &entities, std::vector<enemy> &enemies)
{
    for(unsigned int i=0; i < entities.size(); i++)
    {
        int collisionIndex = this->checkCollision(entities[i]->getHitbox());
        if(collisionIndex)
            {
                int flag = 0;
                flag = entities[i]->getType();
                ///////// CHECK WHETHER  THE COLLIDING OBJECT IS A COING
                if(flag == 1)
                {
                    coinsObtained++;
                    entities.erase(entities.begin() + i);
                    return 0; // no collision, becouse the coin dissapaerd;
                }
                /////////////////

                else if(flag == 2)
                {
                    posX = 0;
                    posY =720;
                }
                return collisionIndex;

            }
    }

    for(unsigned int i=0; i <enemies.size(); i++)
    {
        int collisionIndex = this->checkCollision(enemies[i].getHitbox());
        if(collisionIndex == 4)
        {
            enemies.erase(enemies.begin() + i);
        }
        else if(collisionIndex!=0)
        {
            posX = 0;
            posY =720;
        }
        return collisionIndex;
    }

    return 0;
}

void mario::move(std::vector<entity*> &entities, std::vector<enemy> &enemies, float timePassed)
{
    posY += (velY * timePassed);
    collider.y = posY;

    posX += (velX * timePassed);
    collider.x = posX;

    collisionIndex = this->collision(entities, enemies);


    if (collisionIndex == 1 || collisionIndex == 4)
    {
        if(collisionIndex == 4)
            doubleJump = 0;

        posY -= velY * timePassed;
        collider.y = posY;
        velY = 0;
    }

    else if(collisionIndex == 2 || collisionIndex == 3)
    {
        posX -= velX * timePassed;
        collider.x = posX;
        velX = 0;
    }

    else if(collisionIndex == 0)
    {
        velY += GRAVITY * timePassed;
    }

    if(posY > 800)
    {
        posX = 0;
        posY =720;
    }

}

std::string mario::getCoins()
{
    std::string napis;
    std::stringstream konwersja;
    konwersja << coinsObtained;
    napis = konwersja.str();
    return napis;
}

int mario::getState()
{
    if (collisionIndex == 0 && state == characterState(fall))
        state = characterState(fall);
    else if(velY >= 0 && velY < 20 && velX == 0)
        state = characterState(stand);
    else if(velY >= 0 && velY < 20 && velX != 0)
        state = characterState(walk);
    else
        state = characterState(fall);

    if(velX > 0)
        direction = true;
    else if(velX < 0)
        direction = false;

    return state;
}

void mario::renderMario(SDL_Renderer* renderer, int camX, int camY)
{
    this->getState();

    cTexture pom;

    if((collisionIndex == 0 && velY == 0) || (state == characterState(fall)))
    {
        pom.loadFromFile(animPaths[3], renderer);

        if(direction == true)
            pom.render(posX - camX, posY - camY, renderer);
        else
            pom.renderMirrored(posX - camX, posY - camY, renderer);

        animationIndex = 0;
    }
    else if(state == characterState(walk))
    {
        pom.loadFromFile(animPaths[animationIndex/3], renderer);

        if(direction == true)
            pom.render(posX - camX, posY - camY, renderer);
        else
            pom.renderMirrored(posX - camX, posY - camY, renderer);

        animationIndex++;
        if(animationIndex==9)
            animationIndex=0;
    }
    else if(state == characterState(stand))
    {
        pom.loadFromFile(texturePath, renderer);
        if(direction == false)
            pom.renderMirrored(posX - camX, posY - camY, renderer);
        else
            pom.render(posX - camX, posY - camY, renderer);

        collider.h = pom.getHeight();
        collider.w = pom.getWidth();

        collider.x = posX;
        collider.y = posY;

        animationIndex = 0;
    }
    pom.free();
}

float mario::getPosX()
{
    return posX;
}

float mario::getPosY()
{
    return posY;
}

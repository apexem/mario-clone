#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <cstdio>
#include <vector>
#include "cTexture.h"
#include "mario.h"
#include "cTimer.h"
#include "defines.h"
#include "enemy.h"
#include <cstdlib>
#include <ctime>

SDL_Renderer* renderer;
SDL_Window* okno;

mario cMario;

std::vector<entity*> entities;
std::vector<enemy> enemies;

void initSDL()
{
    // inicjalizacja bibliotek
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();
    // liniowe filtrowanie tekstur
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    // stworzenie okna
    okno = SDL_CreateWindow( "MARIO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, LEVEL_HEIGHT, SDL_WINDOW_SHOWN );
    // stworzenie renderera i ustawienie jego koloru
    renderer = SDL_CreateRenderer(okno, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    SDL_SetRenderDrawColor(renderer, 135, 206, 250, 0xFF );

}

void close()
{
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(okno);
	okno = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}
    // rendering function
void draw(SDL_Renderer* renderer, int camX, int camY)
{
    SDL_RenderClear(renderer);

    cTexture pom;
    pom.loadFromFile("decorations/castle.jpg", renderer);
    pom.render(2080 - camX, 527 - camY, renderer);

    for(unsigned int i = 0;i<entities.size();i++)
    {
        entities[i]->render(renderer, camX, camY);
    }

    for(unsigned int i = 0;i<enemies.size();i++)
    {
        enemies[i].render(renderer, camX, camY);
    }
    cMario.renderMario(renderer, camX, camY);


    pom.loadFromFile("decorations/sun.jpg", renderer);
    pom.render(100 - camX, 100 - camY, renderer);

    pom.loadFromFile("decorations/cloud.bmp", renderer);

    { // clouds placement
    pom.render(300 - camX, 70 - camY, renderer);
    pom.render(500 - camX, 110 - camY, renderer);
    pom.render(700 - camX, 60 - camY, renderer);
    pom.render(823 - camX, 130 - camY, renderer);
    pom.render(930 - camX, 102 - camY, renderer);
    pom.render(1025 - camX, 68 - camY, renderer);
    pom.render(1100 - camX, 125 - camY, renderer);
    pom.render(1232 - camX, 100 - camY, renderer);
    pom.render(1350 - camX, 69 - camY, renderer);
    pom.render(1400 - camX, 93 - camY, renderer);
    pom.render(1464 - camX, 40 - camY, renderer);
    pom.render(1582 - camX, 130 - camY, renderer);
    pom.render(1666 - camX, 62 - camY, renderer);
    pom.render(1734 - camX, 103 - camY, renderer);
    pom.render(1811 - camX, 130 - camY, renderer);
    pom.render(1903 - camX, 38 - camY, renderer);
    pom.render(1999 - camX, 128 - camY, renderer);
    pom.render(2068 - camX, 93 - camY, renderer);
    pom.render(2121 - camX, 75 - camY, renderer);
    pom.render(2200 - camX, 54 - camY, renderer);
    pom.render(2311 - camX, 38 - camY, renderer);
    pom.render(2402 - camX, 23 - camY, renderer);
    pom.render(2520 - camX, 60 - camY, renderer);
    pom.render(2650 - camX, 30 - camY, renderer);
    pom.render(2734 - camX, 83 - camY, renderer);
    pom.render(2840 - camX, 30 - camY, renderer);
    pom.render(2940 - camX, 15 - camY, renderer);
    pom.render(3034 - camX, 70 - camY, renderer);
    pom.render(3150 - camX, 80 - camY, renderer);
    pom.render(3243 - camX, 45 - camY, renderer);
    pom.render(3360 - camX, 34 - camY, renderer);
    pom.render(3455 - camX, 73 - camY, renderer);

    }

    pom.free();

    pom.loadText(cMario.getCoins(), renderer);
    pom.render(0, 0, renderer);

    if(cMario.getCoins() == "23")
    {
        pom.loadText("CONGRATULATIONS! YOU WIN!", renderer);
        pom.render(340, 300, renderer);
    }

    SDL_RenderPresent(renderer);
}
// putting the objects in a single vector
void setObjects()
{
    /////////////////// OBSTACLES
    for(int i=0; i<60;i++)
    {
        entities.push_back(new entity(i*32, 770, "obstacles/brick.bmp"));
    }

    for (int i=0; i<6; i ++)
    {
        entities.push_back(new entity(600+i*32,600, "obstacles/brick.bmp"));
        if(i%2)
            entities.push_back(new entity(580+i*32, 560, "obstacles/coin.jpg"));
    }

    for(int i=0; i<10; i++)
    {
        entities.push_back(new entity(200+i*32, 500, "obstacles/brick.bmp"));
        if(i%2)
            entities.push_back(new entity(180+i*32, 460, "obstacles/coin.jpg"));
    }

    for(int i=0; i<15; i++)
    {
        entities.push_back(new entity(930+i*32, 735, "obstacles/spike.jpg"));
    }

    for(int i=0; i<13; i++)
    {
        entities.push_back(new entity(400+i*32, 330, "obstacles/brick.bmp"));
    }

    entities.push_back(new entity(300, 740, "obstacles/pipe.jpg"));
    entities.push_back(new entity(1650, 570 , "obstacles/pipe.jpg"));
    entities.push_back(new entity(670, 300, "obstacles/pipe.jpg"));

    for(int i=0; i<10; i++)
    {
        entities.push_back(new entity(1000 + i*32 , 400, "obstacles/greenBlock.jpg"));
        if(i%2)
            entities.push_back(new entity(1000+i*32, 360, "obstacles/coin.jpg"));

        entities.push_back(new entity(1500 + i*32 , 600, "obstacles/greenBlock.jpg"));
        entities.push_back(new entity(2000 + i*32 , 700, "obstacles/redBlock.jpg"));
        if(i%2)
            entities.push_back(new entity(1500+i*32, 560, "obstacles/coin.jpg"));
    }

    entities.push_back(new entity(2500, 600, "obstacles/cloud.jpg"));
    entities.push_back(new entity(2600, 500, "obstacles/cloud.jpg"));
    entities.push_back(new entity(2700, 470, "obstacles/cloud.jpg"));
    entities.push_back(new entity(2900, 400, "obstacles/cloud.jpg"));
    entities.push_back(new entity(3254, 368, "obstacles/cloud.jpg"));

    entities.push_back(new entity(2500, 565, "obstacles/coin.jpg"));
    entities.push_back(new entity(2600, 465, "obstacles/coin.jpg"));
    entities.push_back(new entity(2700, 435, "obstacles/coin.jpg"));
    entities.push_back(new entity(2900, 365, "obstacles/coin.jpg"));
    entities.push_back(new entity(3254, 333, "obstacles/coin.jpg"));



    ///////////////////////////

    //////////////////////////// MONSTERS
    enemy koopa(500, 283, 400, 630, "koopa.bmp");
    enemies.push_back(koopa);
    enemy goomba(1000, 370, 999, 1300, "goomba.bmp");
    enemies.push_back(goomba);
    enemy bowser(2050, 630, 2000, 2300, "bowser.bmp");
    enemies.push_back(bowser);
    ////////////////////////////


}
// setting camera
void setCamera(SDL_Rect& camera)
{
    if( cMario.getPosX() < 590)
            camera.x = 0;
    else
        camera.x = (cMario.getPosX() + 32 / 2) - SCREEN_WIDTH / 2;

    if (camera.x > LEVEL_WIDTH - camera.w)
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if (camera.y > LEVEL_HEIGHT - camera.h)
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

int main(int argc, char* argv[])
{
    std::srand( time( NULL ) );
    initSDL();
    SDL_Event e;
    bool quit = false;
    cTimer stepTimer;
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, LEVEL_HEIGHT};
    setObjects();
    // game loop
    while(!quit)
    {
        while(SDL_PollEvent(&e)!=0)
        {
            if(e.type == SDL_QUIT)
                quit = true;
            cMario.input(e);
        }

        float deltaTime = stepTimer.getTime() / 1000.f;

        stepTimer.start();
        cMario.move(entities, enemies, deltaTime);

        for(unsigned int i=0;i<enemies.size();i++)
        {
            enemies[i].move(deltaTime);
        }

        setCamera(camera);


        draw(renderer, camera.x, camera.y);
    }

    close();
    system ("PAUSE");
}

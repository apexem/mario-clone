#ifndef CTEXTURE_CPP_INCLUDED
#define CTEXTURE_CPP_INCLUDED

#include "cTexture.h"

cTexture::cTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

cTexture::~cTexture()
{
    free();
}

void cTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    free();
    SDL_Texture* pomText = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF));
    pomText = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);
    mTexture = pomText;

}

void cTexture::loadText(std::string text, SDL_Renderer* renderer)
{
    free();

    TTF_Font* mFont;

    SDL_Color textColor = {0, 0, 0};
    mFont = TTF_OpenFont("font.ttf", 40);
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(mFont, text.c_str(), textColor );
    mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    mWidth = textSurface->w;
    mHeight = textSurface->h;

    TTF_CloseFont(mFont);
}

void cTexture::render(int x, int y, SDL_Renderer* renderer)
{
    SDL_Rect renderRect = {x, y, mWidth, mHeight};
    SDL_RenderCopy(renderer, mTexture, NULL, &renderRect);
}

void cTexture::renderMirrored(int x, int y, SDL_Renderer* renderer)
{
    SDL_Rect renderRect = {x, y, mWidth, mHeight};
    SDL_RenderCopyEx(renderer, mTexture, NULL, &renderRect, 0, NULL, SDL_FLIP_HORIZONTAL);
}

void cTexture::free()
{
    if(mTexture!=NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture=NULL;
        mWidth=0;
        mHeight=0;
    }
}

float cTexture::getWidth()
{
    return mWidth;
}

float cTexture::getHeight()
{
    return mHeight;
}



#endif // CTEXTURE_CPP_INCLUDED

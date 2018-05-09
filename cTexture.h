#ifndef CTEXTURE_H_INCLUDED
#define CTEXTURE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class cTexture
{
    public:
        cTexture();
        cTexture(float x, float y, std::string path);
        ~cTexture();
        void free();

        void loadText(std::string text, SDL_Renderer* renderer);
        void loadFromFile(std::string path, SDL_Renderer* renderer);
        void render(int x, int y, SDL_Renderer* renderer);
        void renderMirrored(int x, int y, SDL_Renderer* renderer);

        float getWidth();
        float getHeight();

    private:
        SDL_Texture* mTexture;
        float mWidth;
        float mHeight;
};

#endif // CTEXTURE_H_INCLUDED

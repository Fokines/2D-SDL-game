#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

using namespace std;

class Entity
{
protected:
    float x, y;
    int h, w;
    SDL_Rect currentFrame;
    SDL_Texture * tex = nullptr;
    SDL_Renderer * render;
public:
    float getX() { return x; }

    void setXY(float x, float y)
    {
        this->x = x;
        this->y = y;
        currentFrame.x = x;
        currentFrame.y = y;
    }

    float getY() { return y; }

    int getH() { return h; }

    int getW() { return w; }

    void show()
    {
        currentFrame.x = x;
        currentFrame.y = y;
        SDL_RenderCopy(render, tex, NULL, &currentFrame);
    }

    void loadTexture(const char * filePath)
    {
        if(tex != nullptr) { SDL_DestroyTexture(tex); }

        tex = IMG_LoadTexture(render, filePath);
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        currentFrame.h = h;
        currentFrame.w = w;
    }

    ~Entity()
    {
        SDL_DestroyTexture(tex);
        tex = NULL;
    }
};

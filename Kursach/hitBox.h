#ifndef HITBOX_H
#define HITBOX_H



#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include <iostream>
using namespace std;

class HitBox
{
private:
    SDL_Rect rect;
    SDL_Renderer * render;
public:
    void setInfo(SDL_Renderer * render, float x, float y, int h, int w)
    {
        this->render = render;
        rect.x = x;
        rect.y = y;
        rect.h = h;
        rect.w = w;
    }

    void setX(float x) { rect.x = x; }

    bool inHitBoxRect(float x, float y, int h, int w)
    {
        float pX, pY;
        for(int i = x; i < x + w; i += 10)
        {
            for(int j = y; j < y + h; j += 10)
            {
                pX = i;
                pY = j;
                if((pX > rect.x && pX < rect.x + rect.w) && (pY > rect.y && pY < rect.y + rect.h))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool inHitBoxMouse(float x, float y)
    {
        if((x > rect.x && x < rect.x + rect.w) && (y > rect.y && y < rect.y + rect.h))
        {
            return true;
        }
        return false;
    }

    ~HitBox() { }
};

#endif // HITBOX_H

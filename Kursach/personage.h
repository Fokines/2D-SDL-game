#ifndef PERSONAGE_H
#define PERSONAGE_H

#include "entity.h"
#include "hitBox.h"

class Personage: public Entity
{
private:
    float speed;
    bool turned;
    SDL_Texture * secondaryTex = nullptr;
    SDL_Texture * bufTex = nullptr;
    HitBox hitBox;
public:
    Personage(float speed, SDL_Renderer * render)
    {
        this->render = render;
        this->speed = speed;
        turned = false;
    }

    void moveForward(float timeFrame)
    {
        x += speed * timeFrame;
        hitBox.setX(x + w - 48);
    }

    void moveBack(float timeFrame)
    {
        x -= speed * timeFrame;
        hitBox.setX(x - 6);
    }

    bool isTurned() { return turned; }

    void changeTexture()
    {
        bufTex = tex;
        tex = secondaryTex;
        secondaryTex = bufTex;
        turned = !turned;
    }

    void setInfo()
    {
        hitBox.setInfo(render, x + w /3 * 2 + 4, y + h/2 - 8, 20, 53);
    }

    void loadTexture(const char * filePathMain, const char * filePathSecondary)
    {
        if(tex != nullptr) { SDL_DestroyTexture(tex); }

        if(bufTex != nullptr){ SDL_DestroyTexture(bufTex); }

        if(secondaryTex != nullptr){ SDL_DestroyTexture(secondaryTex); }

        tex = IMG_LoadTexture(render, filePathMain);
        secondaryTex = IMG_LoadTexture(render, filePathSecondary);
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        currentFrame.h = h;
        currentFrame.w = w;
    }

    bool inHitBox(float x, float y, int h, int w) { return hitBox.inHitBoxRect(x, y, h, w); }

    ~Personage()
    {
        if(tex != nullptr)
        {
            SDL_DestroyTexture(tex);
            tex = NULL;
        }
        if(bufTex != nullptr)
        {
            SDL_DestroyTexture(bufTex);
            bufTex = NULL;
        }
        if(secondaryTex != nullptr)
        {
            SDL_DestroyTexture(secondaryTex);
            secondaryTex = NULL;
        }
    }
};
#endif // PERSONAGE_H

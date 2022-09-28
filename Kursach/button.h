#ifndef BUTTON_H
#define BUTTON_H

#include "entity.h"
#include "hitBox.h"

class Button: public Entity
{
private:

    HitBox hitBox;
    SDL_Texture * secondaryTex = nullptr;
    SDL_Texture * bufTex;
    bool push = false;

public:
    Button(SDL_Renderer * render) { this->render = render; }

    void setInfo() { hitBox.setInfo(render, x, y, h, w); }

    bool inHitBox(float x, float y) { return hitBox.inHitBoxMouse(x, y); }

    void loadTexture(const char* filePathMain, const char* filePathSecondary)
    {
        if(tex != nullptr) { SDL_DestroyTexture(tex); }

        if(secondaryTex != nullptr) { SDL_DestroyTexture(secondaryTex); }

        tex = IMG_LoadTexture(render, filePathMain);
        secondaryTex = IMG_LoadTexture(render, filePathSecondary);
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        currentFrame.h = h;
        currentFrame.w = w;
    }

    void changeTexture()
    {
        bufTex = tex;
        tex = secondaryTex;
        secondaryTex = bufTex;
        push = !push;
    }

    bool getPush() { return push; }

    ~Button()
    {
        if(tex != nullptr)
        {
            SDL_DestroyTexture(tex);
            tex = NULL;
        }

        if(secondaryTex != nullptr)
        {
            SDL_DestroyTexture(secondaryTex);
            secondaryTex = NULL;
        }
    }
};

#endif // BUTTON_H

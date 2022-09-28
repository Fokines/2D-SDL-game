#ifndef STATICPICTURES_H
#define STATICPICTURES_H

#include "entity.h"

#include <iostream>

using namespace std;

class StaticPictues: public Entity
{
public:
    StaticPictues(SDL_Renderer * render) { this->render = render; }

    ~StaticPictues()
    {
        SDL_DestroyTexture(tex);
        tex = NULL;
    }
};

#endif // STATICPICTURES_H

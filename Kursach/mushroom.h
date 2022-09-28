#ifndef MUSHROOM_H
#define MUSHROOM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.h"

class Mushroom: public Entity
{
private:
    int points;
    float speed;
    bool poisonous;
public:
    Mushroom(float speed, SDL_Renderer * render)
    {
        this->speed = speed;
        this->render = render;
    }

    bool getPoisonous() { return poisonous; }

    int getPoints() { return points; }

    void setSpeed(float speed) { this->speed = speed; }

    void moveY(float timeFrame) { y += speed * timeFrame; }

    void create(int coin, int type, int x)
    {
        const char* filePath;
        if(coin < 80)
        {
            poisonous = false;
            switch (type)
            {
                case 0:
                filePath = "grf/podosinovik.png";
                points = 8;
                break;
                case 1:
                filePath = "grf/bely.png";
                points = 10;
                break;
                case 2:
                filePath = "grf/lisichki.png";
                points = 5;
                break;
                case 3:
                filePath = "grf/podberezovik.png";
                points = 8;
                break;
                case 4:
                filePath = "grf/syroezhki.png";
                points = 2;
                break;
            }
        }
        else
        {
            poisonous = true;
            switch (type)
            {
                case 0:
                filePath = "grf/mukhomor.png";
                points = -10;
                break;
                case 1:
                filePath = "grf/poganki.png";
                points = -10;
                break;
            }
        }
        this->loadTexture(filePath);
        this->setXY(x, 0);
    }

    ~Mushroom()
    {
        if(tex != nullptr)
        {
            SDL_DestroyTexture(tex);
            tex = NULL;
        }
    }
};
#endif // MUSHROOM_H

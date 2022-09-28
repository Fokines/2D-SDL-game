#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "staticPictures.h"
#include "button.h"
#include "text.h"
#include "time.h"

#define HEIGHT 600
#define WIDTH 1200

#undef enterName

string name;

int enterNameMenu (SDL_Renderer * render)
{
    setlocale(LC_ALL, " Russian");

    SDL_Event event;

    StaticPictues * backTexture = new StaticPictues(render);
    backTexture->loadTexture("grf/backMenu.png");
    backTexture->setXY(0, 0);

    StaticPictues * enterName = new StaticPictues(render);
    enterName->loadTexture("grf/enter_name.png");
    enterName->setXY(WIDTH/2-enterName->getW()/2 + 280, HEIGHT/2-enterName->getH() + 150);

    StaticPictues * creator = new StaticPictues(render);
    creator->loadTexture("grf/NAME.png");
    creator->setXY(WIDTH/2-creator->getW() + 20, HEIGHT/2-creator->getH() + 200);

    Button * inputName = new Button(render);
    inputName->loadTexture("grf/enter2name.png", "grf/enter2namePUSH.png");
    inputName->setXY(WIDTH/2-inputName->getW()/2 + 280, HEIGHT/2+inputName->getH() + 30);
    inputName->setInfo();

    Text * text = new Text(255, 255, 255, 25, render);
    text->loadTTF("ttf/arial.ttf");
    text->loadTexture();
    text->setXY(WIDTH/2-text->getW()/2, HEIGHT/2-text->getH());

    name = "";

    bool menu = true;
    int returnMenu = -1;
    while(menu)
    {
        while(SDL_PollEvent(&event))
        {
            int time = clock();
            switch (event.type)
            {
            case SDL_QUIT:
                menu = false;
                returnMenu = -1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(inputName->inHitBox(event.motion.x, event.motion.y))
                    {
                        inputName->changeTexture();
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(inputName->getPush())
                    {
                        inputName->changeTexture();
                    }
                    if(inputName->inHitBox(event.motion.x, event.motion.y))
                    {
                        if(name != "")
                        {
                            SDL_RenderClear(render);
                            returnMenu = 1;
                            menu = false;
                        }
                    }
                }
                break;
            case SDL_TEXTINPUT:
                name += event.text.text;
                text->setText(name);
                text->setXY(WIDTH/2-text->getW()/2 + 300, HEIGHT/2+text->getH() + 30);
                break;
            }
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && name.length() > 0 && (int)event.key.timestamp != time)
            {
                time = event.key.timestamp;
                name.pop_back();
                text->setText(name);
                text->setXY(WIDTH/2-text->getW()/2 + 300, HEIGHT/2+text->getH() + 30);
            }
        }
        SDL_RenderClear(render);

        backTexture->show();
        enterName->show();
        inputName->show();
        creator->show();
        text->show();

        SDL_RenderPresent(render);
    }
    SDL_RenderClear(render);
    delete backTexture;
    delete enterName;
    delete inputName;
    delete creator;
    delete text;
    return returnMenu;
}

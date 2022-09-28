#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "staticPictures.h"
#include "button.h"
#include "text.h"
#include "player.h"

#define HEIGHT 600
#define WIDTH 1200
#define R 10

#undef showRecords

int showRecords(SDL_Renderer * render,  Player * players[R]){
    SDL_Event event;

    StaticPictues * backTexture = new StaticPictues(render);
    backTexture->loadTexture("grf/backMenu.png");
    backTexture->setXY(0, 0);

    Button  * backToMenu = new Button(render);
    backToMenu->loadTexture("grf/backtomenuNoPush.png", "grf/backtomenuPush.png");
    backToMenu->setXY(WIDTH/2 - backToMenu->getW()/2, HEIGHT/2 + backToMenu->getH());
    backToMenu->setInfo();

    Text *text[R];
    for(int i = 0; i < R; i++)
    {
        text[i] = new Text(255, 255, 255, 25, render);
        text[i]->loadTTF("ttf/arial.ttf");
        text[i]->loadTexture();
        if(players[i] != NULL)
        {
            string str = "Игрок ";
            str += players[i]->getPlayerName();
            str += ", его счёт: ";
            str += to_string(players[i]->getScore());
            text[i]->setText(str);
        }
        text[i]->setXY(WIDTH/2 - text[i]->getW()/2, text[i]->getH()*i);
    }

    bool menu = true;
    int returnMenu = -1;
    while(menu)
    {
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                menu = false;
                returnMenu = -1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(backToMenu->inHitBox(event.motion.x, event.motion.y))
                    {
                        backToMenu->changeTexture();
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(backToMenu->getPush())
                    {
                        backToMenu->changeTexture();
                    }
                    if(backToMenu->inHitBox(event.motion.x, event.motion.y))
                    {
                        SDL_RenderClear(render);
                        returnMenu = 1;
                        menu = false;
                    }
                }
                break;
            }
        }
        SDL_RenderClear(render);

        backTexture->show();
        backToMenu->show();
        for(int i = 0; i < R; i++)
        {
            text[i]->show();
        }
        SDL_RenderPresent(render);
    }
    SDL_RenderClear(render);
    delete backTexture;
    delete backToMenu;
    return returnMenu;
    return 1;
}

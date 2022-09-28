#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "staticPictures.h"
#include "button.h"
#include "player.h"

#define HEIGHT 600
#define WIDTH 1200

#undef gameRules

int gameRules(SDL_Renderer * render)
{
    SDL_Event event;

    StaticPictues * backTexture = new StaticPictues(render);
    backTexture->loadTexture("grf/backMenuDark.png");
    backTexture->setXY(0, 0);

    Button * backToMenu = new Button(render);
    backToMenu->loadTexture("grf/backtomenuNoPush.png", "grf/backtomenuPush.png");
    backToMenu->setXY(WIDTH/2-backToMenu->getW()/2, HEIGHT/2 + (100 + backToMenu->getH()));
    backToMenu->setInfo();

    StaticPictues * RulesAndMush = new StaticPictues(render);
    RulesAndMush->loadTexture("grf/finalgameROOLS.png");
    RulesAndMush->setXY(0, 0);

    bool menu = true;
    int returnMenu = -1;
    while(menu)
    {
        while(SDL_PollEvent(&event))
        {
           //int time = clock();
            switch (event.type){
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
        RulesAndMush->show();

        SDL_RenderPresent(render);
    }
    SDL_RenderClear(render);
    delete backTexture;
    delete backToMenu;
    delete RulesAndMush;
    return returnMenu;
}

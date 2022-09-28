#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "staticPictures.h"
#include "button.h"

#define HEIGHT 600
#define WIDTH 1200

#undef mainMenu

int mainMenu(SDL_Renderer * render)
{
    SDL_Event event;

    StaticPictues * backTexture = new StaticPictues(render);
    backTexture->loadTexture("grf/backMenu.png");
    backTexture->setXY(0, 0);

    Button * startGameButtom = new Button(render);
    startGameButtom->loadTexture("grf/start.png", "grf/startPush.png");
    startGameButtom->setXY(WIDTH/2-startGameButtom->getW()/2, HEIGHT/2-startGameButtom->getH()*2);
    startGameButtom->setInfo();

    Button * quittingTheGame = new Button(render);
    quittingTheGame->loadTexture("grf/exitgameNoPush.png", "grf/exitgamePush.png");
    quittingTheGame->setXY(WIDTH/2-quittingTheGame->getW()/2, HEIGHT/2+quittingTheGame->getH()*2);
    quittingTheGame->setInfo();

    Button * showRecords = new Button(render);
    showRecords->loadTexture("grf/records.png", "grf/recordsPUSH.png");
    showRecords->setXY(WIDTH/2-showRecords->getW()/2, HEIGHT/2+showRecords->getH());
    showRecords->setInfo();

    Button * chandePlayer = new Button(render);
    chandePlayer->loadTexture("grf/switchplayer.png", "grf/switchplayerPUSH.png");
    chandePlayer->setXY(WIDTH/2-chandePlayer->getW()/2, HEIGHT/2-chandePlayer->getH());
    chandePlayer->setInfo();

    Button * gameRules = new Button(render);
    gameRules->loadTexture("grf/gameRollsNoPush.png", "grf/gameRollsPush.png");
    gameRules->setXY(WIDTH/2-gameRules->getW()/2, HEIGHT/2);
    gameRules->setInfo();

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
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(startGameButtom->inHitBox(event.motion.x, event.motion.y))
                    {
                        startGameButtom->changeTexture();
                    }
                    if(quittingTheGame->inHitBox(event.motion.x, event.motion.y))
                    {
                        quittingTheGame->changeTexture();
                    }
                    if(showRecords->inHitBox(event.motion.x, event.motion.y))
                    {
                        showRecords->changeTexture();
                    }
                    if(chandePlayer->inHitBox(event.motion.x, event.motion.y))
                    {
                        chandePlayer->changeTexture();
                    }
                    if(gameRules->inHitBox(event.motion.x, event.motion.y))
                    {
                        gameRules->changeTexture();
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    if(startGameButtom->getPush())
                    {
                        startGameButtom->changeTexture();
                    }
                    if(startGameButtom->inHitBox(event.motion.x, event.motion.y))
                    {
                        SDL_RenderClear(render);
                        returnMenu = 2;
                        menu = false;
                    }
                    if(quittingTheGame->getPush())
                    {
                        quittingTheGame->changeTexture();
                    }
                    if(quittingTheGame->inHitBox(event.motion.x, event.motion.y))
                    {
                        SDL_RenderClear(render);
                        returnMenu = -1;
                        menu = false;
                    }
                    if(showRecords->getPush())
                    {
                        showRecords->changeTexture();
                    }
                    if(showRecords->inHitBox(event.motion.x, event.motion.y))
                    {
                        SDL_RenderClear(render);
                        returnMenu = 3;
                        menu = false;
                    }
                    if(chandePlayer->getPush())
                    {
                        chandePlayer->changeTexture();
                    }
                    if(chandePlayer->inHitBox(event.motion.x, event.motion.y))
                    {
                        SDL_RenderClear(render);
                        returnMenu = 0;
                        menu = false;
                    }
                    if(gameRules->getPush())
                    {
                        gameRules->changeTexture();
                    }
                    if(gameRules->inHitBox(event.motion.x, event.motion.y))
                    {
                        SDL_RenderClear(render);
                        returnMenu = 4;
                        menu = false;
                    }
                }
                break;
            }
        }
        SDL_RenderClear(render);

        backTexture->show();
        startGameButtom->show();
        gameRules->show();
        quittingTheGame->show();
        showRecords->show();
        chandePlayer->show();


        SDL_RenderPresent(render);
    }
    SDL_RenderClear(render);
    delete backTexture;
    delete startGameButtom;
    delete quittingTheGame;
    delete showRecords;
    delete gameRules;
    return returnMenu;
}

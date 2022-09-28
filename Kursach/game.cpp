#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <ctime>
#include <time.h>

#include "mushroom.h"
#include "personage.h"
#include "staticPictures.h"
#include "button.h"

#define HEIGHT 600
#define WIDTH 1200
#define N 6

#undef game

int score;

int getRandInt(int min, int  max){
    int q = (min + rand() % (max - min + 1));
    return q;
}

double getRandDouble(double min, double  max){
    return (min + (double)rand() / RAND_MAX * (max - min));
}

int game(SDL_Renderer * render){
    srand(time(NULL));

    int hp = 3;
    score = 0;
    float minSpeed = 60;
    float maxSpeed = 250;
    float PersonageSpeed = 500;
    bool gameRunning = true;
    bool pause = false;
    bool loose = false;
    int timeStart;

    SDL_Event event;

    StaticPictues * backTexture = new StaticPictues(render);
    backTexture->loadTexture("grf/fon.png");
    backTexture->setXY(0, 0);

    StaticPictues * endGame = new StaticPictues(render);
    endGame->loadTexture("grf/gameOVER.png");
    endGame->setXY(WIDTH/2 - endGame->getW()/2, HEIGHT/2 - endGame->getH());

    Personage * player = new Personage(PersonageSpeed, render);
    player->loadTexture("grf/pers.png", "grf/pers1.png");
    player->setXY(WIDTH/2 - player->getW(), HEIGHT - player->getH());
    player->setInfo();

    Button * continueButton = new Button(render);
    continueButton->loadTexture("grf/continueNoPush.png", "grf/continuePush.png");
    continueButton->setXY(WIDTH/2 - continueButton->getW()/2, HEIGHT/2 - continueButton->getH());
    continueButton->setInfo();

    Button * backToMenu = new Button(render);
    backToMenu->loadTexture("grf/backtomenuNoPush.png", "grf/backtomenuPush.png");
    backToMenu->setXY(WIDTH/2 - backToMenu->getW()/2, HEIGHT/2 + backToMenu->getH()/2);
    backToMenu->setInfo();

    Mushroom *mushroom[N];
    for(int i = 0; i < N; i++){
        int coin = getRandInt(0, 1);
        int x = getRandInt(100, WIDTH - 100);
        mushroom[i] = new Mushroom(getRandDouble(minSpeed, maxSpeed), render);
        if(coin < 80){
            mushroom[i]->create(coin, getRandInt(0, 4), x);
        }else{
            mushroom[i]->create(coin, getRandInt(0, 1), x);
        }
    }

    timeStart = clock();

    float curtimeFrame = SDL_GetTicks() / 1000.0;
    float prevtimeFrame;
    float dtimeFrame;
    while(gameRunning) {
        prevtimeFrame = curtimeFrame;
        curtimeFrame = SDL_GetTicks() / 1000.0;
        dtimeFrame = curtimeFrame - prevtimeFrame;
        if(hp == 0){
            loose = true;
        }
        while(SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_QUIT:
                gameRunning = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(continueButton->inHitBox(event.motion.x, event.motion.y)){
                        continueButton->changeTexture();
                    }
                    if(backToMenu->inHitBox(event.motion.x, event.motion.y)){
                        backToMenu->changeTexture();
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(continueButton->getPush()){
                        continueButton->changeTexture();
                    }
                    if(continueButton->inHitBox(event.motion.x, event.motion.y)){
                        SDL_RenderClear(render);
                        pause = false;
                    }
                    if(backToMenu->getPush()){
                        backToMenu->changeTexture();
                    }
                    if(backToMenu->inHitBox(event.motion.x, event.motion.y)){
                        SDL_RenderClear(render);
                        gameRunning = false;
                    }
                }
                break;
            }
            if(event.key.keysym.sym == SDLK_d && !pause && !loose){
                if(player->getX() < WIDTH - player->getW()){
                    if(player->isTurned()){
                        player->changeTexture();
                    }
                    player->moveForward(dtimeFrame);
                }
            }
            if(event.key.keysym.sym == SDLK_a && !pause && !loose){
                if(player->getX() >= 0){
                    if(!player->isTurned()){
                        player->changeTexture();
                    }
                    player->moveBack(dtimeFrame);
                }
            }
            if(event.key.keysym.sym == SDLK_SPACE && !pause && !loose){
                pause = !pause;
            }
        }

        SDL_RenderClear(render);
        backTexture->show();

        if(score <= 99999){
            int k = 1;
            StaticPictues *point = new StaticPictues(render);
            string st = "grf/";
            if(score == 0){
                st+=to_string(0);
                st+=" (1).png";
                point->loadTexture(st.c_str());
                point->setXY(WIDTH - point->getW() * k - 10, 0);
                point->show();
            }else{
                for(int i = score; i > 0; i = i/10, k++){
                    int j = i%10;
                    st = "grf/";
                    st+=to_string(j);
                    st+=" (1).png";
                    point->loadTexture(st.c_str());
                    point->setXY(WIDTH-point->getW()*k-10, 0);
                    point->show();
                }
            }
            delete point;
        }

        if(hp > 0){
            string st = "grf/";
            st+=to_string(hp);
            st+=".png";
            StaticPictues *hpE = new StaticPictues(render);
            hpE->loadTexture(st.c_str());
            hpE->setXY(0, 0);
            hpE->show();
            delete hpE;
        }

        player->show();

        for(int i = 0; i < N; i++){
            int speedCoefficient = (clock() - timeStart) / 100000;
            int coin = getRandInt(0, 100);
            int type;
            int x = getRandInt(100, WIDTH-100);
            if(coin < 80){
                type = getRandInt(0, 4);
            }else {
                type = getRandInt(0, 1);
            }
            if(!pause && !loose){
                mushroom[i]->moveY(dtimeFrame);
            }
            if(mushroom[i]->getY() > HEIGHT-80){
                mushroom[i]->create(coin, type, x);
                mushroom[i]->setSpeed(getRandDouble(minSpeed+minSpeed*speedCoefficient, maxSpeed+maxSpeed*speedCoefficient));
            }
            if(player->inHitBox(mushroom[i]->getX(), mushroom[i]->getY(), mushroom[i]->getH(), mushroom[i]->getW())){
                if(mushroom[i]->getPoisonous()){
                    hp--;
                }
                score += mushroom[i]->getPoints();
                if(score < 0){
                    score = 0;
                };
                mushroom[i]->create(coin, type, x);
                mushroom[i]->setSpeed(getRandDouble(minSpeed+minSpeed*speedCoefficient, maxSpeed+maxSpeed*speedCoefficient));
            }
            mushroom[i]->show();
        }
        if(pause || loose){
            if(loose){
                endGame->show();
            }else{
                continueButton->show();
            }
            backToMenu->show();
        }
        SDL_RenderPresent(render);
    }
    SDL_RenderClear(render);
    delete backTexture;
    delete player;
    delete continueButton;
    for(int i = 0; i < N; i++){
        delete mushroom[i];
        mushroom[i] = NULL;
    }
    delete backToMenu;
    return -2;
}

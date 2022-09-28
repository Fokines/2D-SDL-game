#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "mushroom.h"
#include "personage.h"
#include "staticPictures.h"
#include "button.h"
#include "player.h"

#define HEIGHT 600
#define WIDTH 1200
#define N 6
#define R 10

#undef main

extern int score;
extern string name;

int mainMenu(SDL_Renderer* render);
int game(SDL_Renderer * render);
int enterNameMenu (SDL_Renderer * render);
int showRecords(SDL_Renderer * render,  Player * players[R]);
int gameRules(SDL_Renderer * render);


int main(){
    system("chcp 65001 & cls");

    if(SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        cout << "Не удалось выполнить SDL_Init. SDL_ERROR: "<< SDL_GetError() << endl;
    }

    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "1");

    if(!(IMG_Init(IMG_INIT_PNG)))
    {
        cout << "Не удалось выполнить IMG_Init. Error: " << IMG_GetError() << endl;
    }

    if(TTF_Init() > 0)
    {
        cout << "Не удалось выполнить TTF_Init. Error: "<< TTF_GetError() << endl;
    }

    SDL_Window * window = SDL_CreateWindow("Mushroomer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer * render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    int r = 0;
    Player *players[R];
    const char* fileName = "scores.txt";
    ifstream in(fileName);
    for(int i = 0; i < R; i++)
    {
        players[i] = new Player();
        if(players[i]->readScore(in))
        {
            r++;
        }
        else
        {
            players[i] = NULL;
        }
    }
    in.close();
    bool mainLoop = true;
    int mainFlag = 0;
    while(mainLoop)
    {
        switch (mainFlag)
        {
        case 0:
            mainFlag = enterNameMenu(render);
            break;
        case 1:
            mainFlag = mainMenu(render);
            break;
        case 2:
            mainFlag = game(render);
            break;
        case 3:
            mainFlag = showRecords(render, players);
            break;
        case 4:
            mainFlag = gameRules(render);
            break;
        case -1:
            mainLoop = false;
            break;
        case -2:
            bool additionalFlag = true;
            for(int i = 0; i < R; i++)
            {
                if(players[i] != NULL)
                {
                    if(players[i]->getPlayerName() == name)
                    {
                        if(players[i]->getScore() < score)
                        {
                            players[i]->setScore(score);
                        }
                        additionalFlag = false;
                    }
                }
            }
            if(additionalFlag)
            {
                if(r == R){
                    int l = 0;
                    for(int i = 0; i < R && players[i] != NULL; i++)
                    {
                        if( players[i]->getScore() < score)
                        {
                            l = i;
                        }
                    }
                    players[l]->setScore(score);
                    players[l]->setPlayerName(name);
                }
                else
                {
                    players[r] = new Player();
                    players[r]->setScore(score);
                    players[r]->setPlayerName(name);
                    r++;
                }
            }
            int bufScore;
            string bufName;
            for(int i = 0; i < R && players[i] != NULL; i++)
            {
                for(int j = 0; j < R && players[j] != NULL; j++)
                {
                    if(players[i]->getScore() > players[j]->getScore())
                    {
                        bufScore = players[i]->getScore();
                        bufName = players[i]->getPlayerName();
                        players[i]->setScore(players[j]->getScore());
                        players[i]->setPlayerName(players[j]->getPlayerName());
                        players[j]->setScore(bufScore);
                        players[j]->setPlayerName(bufName);
                    }
                }
            }
            mainFlag = 1;
            break;
        }
    }
    ofstream on(fileName);
    for(int i = 0; i < R; i++)
    {
        if(players[i] != NULL)
        {
            players[i]->writeScore(on);
        }
    }
    on.close();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    for(int i = 0; i < R; i++)
    {
        if(players[i] != NULL)
        {
            delete players[i];
        }
    }
    return 0;
}



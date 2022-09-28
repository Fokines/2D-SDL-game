#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "entity.h"

class Text: public Entity
{
private:
    TTF_Font * font;
    SDL_Surface * surface;
    SDL_Color color;
    int red = 0, green = 0, blue = 0;
    int ptsize;
    string str = "";
public:
    Text(int red, int green, int blue, int ptsize, SDL_Renderer * render)
    {
        this->render = render;
        this->red = red;
        this->green = green;
        this->blue = blue;
        this->ptsize = ptsize;
        color.a = 0;
        color.r = this->red;
        color.g = this->green;
        color.b = this->blue;
    }

    void setText(string str)
    {
        this->str = str;
        loadTexture();
    }

    void loadTTF(const char * filePath)
    {
        font = TTF_OpenFont(filePath, ptsize);
    }

    void loadTexture()
    {
        surface = TTF_RenderUTF8_Solid(font, str.c_str(), color);

        if(tex != nullptr) { SDL_DestroyTexture(tex); }

        tex = SDL_CreateTextureFromSurface(render, surface);
        SDL_QueryTexture(tex, NULL, NULL, &w, &h);
        currentFrame.h = h;
        currentFrame.w = w;
    }

    ~Text()
    {
        SDL_DestroyTexture(tex);
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
    }
};
#endif // TEXT_H

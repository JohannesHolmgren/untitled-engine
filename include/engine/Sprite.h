/*
    Class Sprite:
    
    The Sprite class wraps an SDL_Texture to 
    increase the convenience and add an interface
    to that class
*/
#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"

class Sprite {
    private:
        SDL_Rect destRect;

    public:
        SDL_Texture* sprite;
        Sprite(SDL_Texture* sprite);
        Sprite(SDL_Texture* sprite, int scale);
        Sprite(SDL_Texture* sprite, int scaleX, int scaleY);
        void render(SDL_Renderer* renderer, int x, int y);
        void scale(int scaleX, int scaleY);
};

#endif
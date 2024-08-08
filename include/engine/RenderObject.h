#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include <SDL2/SDL.h>
#include "State.h"
#include "Sprite.h"

class RenderObject {
    public:
        RenderObject();
        RenderObject(Sprite sprite);
        RenderObject(Sprite sprite, int x, int y);
        void render(SDL_Renderer* renderer);
        virtual void update(State* state) = 0;
        void setPos(int x, int y);
        std::pair<int, int> getPos();
        std::pair<int, int> getSize();
        virtual ~RenderObject();
        void setSprite(Sprite sprite);

    private:
        Sprite sprite = nullptr;     // The texture to be rendered
        SDL_Rect destRect;            // Position and dimensions of where to render on screen

};

#endif
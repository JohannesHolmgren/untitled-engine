/*
    Class Camera

    The world are usually too big for being shown
    on the screen all at once. The Camera Class
    handles which part of the world to be shown.

    The structure of all renerable things are something like this:
    There's a lot of sprites (SDL_Texture*) which should be rendered
    using a renderer (SDL_Renderer)

    Idea:
    - Create a surface/SDL_Texture that is bigger than the screen. 
    - Render sprites to this surface.
    - Render part of this surface (using srcRect) onto the window

    Problems and thoughts:
    - A big "world" texture can reduce performance
    - Could many smaller "worlds" be combined to help with this?
    - Which part of the "world" that will be shown to the window 
      will be known before rendering occurs. Can rendering be confined
      to this part? 
    - If that doesn't work. Render all who collides with the rect describing
      what part of the world to be rendered.
    - Add zoom eventually
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "RenderObject.h"

class Camera {
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* world = nullptr;
        std::shared_ptr<RenderObject> objectInFocus;
        SDL_Rect cameraRect;
        std::pair<int, int> offset{0, 0};
        std::pair<int, int> worldSize;

        void updatePositionFromFocusObject();
        void render(std::vector<std::shared_ptr<RenderObject>>& renderObjects);

    public:
        Camera();
        bool init(int width, int height);
        void quit();
        void setFocusObject(std::shared_ptr<RenderObject> obj);
        void unsetFocusObject();
        void setOffset(int dx, int dy);
        std::pair<int, int> getOffset();
        std::pair<int, int> getPosition();
        std::pair<int, int> getSize();
        SDL_Window* getWindow();
        SDL_Texture* textureFromSurface(SDL_Surface* surface);
        void update(std::vector<std::shared_ptr<RenderObject>>& renderObjects);
};



#endif
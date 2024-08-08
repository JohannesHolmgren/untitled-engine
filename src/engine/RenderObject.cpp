#include "RenderObject.h"
#include <iostream>
#include <string>
#include <utility>
#include <SDL2/SDL.h>

RenderObject::RenderObject() {}

RenderObject::RenderObject(Sprite sprite) {
    this->sprite = sprite;
    destRect = SDL_Rect({0, 0, 0, 0});
    // Get width and height of the sprite and write to destRect
    SDL_QueryTexture(sprite.sprite, NULL, NULL, &destRect.w, &destRect.h);
}

RenderObject::RenderObject(Sprite sprite, int x, int y) {
    this->sprite = sprite;
    destRect = SDL_Rect({x, y, 0, 0});
    SDL_QueryTexture(sprite.sprite, NULL, NULL, &destRect.w, &destRect.h);
}

/**
 * Renders the sprite of the object to the screen using 'destRect'.
 * @param
 * SDL_Renderer* renderer: the renderer of the screen to render to.
 */
void RenderObject::render(SDL_Renderer* renderer) {
    sprite.render(renderer, destRect.x, destRect.y);
    // SDL_RenderCopy(renderer, sprite, NULL, &destRect);
}

/**
 * Base update method for all objects that is called every frame.
 * The base update doesn't do anything and is safe to override without calling 
 * the super method.
 * @param
 * State* state: the state of the engine
 */
void RenderObject::update(State* state) {
}

/**
 * Moves the Object to position (x, y) by moving it's destRect
 */
void RenderObject::setPos(int x, int y) {
    destRect.x = x;
    destRect.y = y;
}

/** 
 * Get the x- and y-component from the object's destRect
 */
std::pair<int, int> RenderObject::getPos() {
    return std::pair<int, int>(destRect.x, destRect.y);
}

std::pair<int, int> RenderObject::getSize() {
    return std::pair<int, int>(destRect.w, destRect.h);
}

void RenderObject::setSprite(Sprite sprite) {
    this->sprite = sprite;
}

RenderObject::~RenderObject() {
    sprite = nullptr;
}
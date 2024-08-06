#include "Sprite.h"

Sprite::Sprite(SDL_Texture* sprite) {
    this->sprite = sprite;
    destRect = SDL_Rect({0, 0, 0, 0});
    SDL_QueryTexture(this->sprite, NULL, NULL, &destRect.w, &destRect.h);
}

Sprite::Sprite(SDL_Texture* sprite, int scaleSize) {
    this->sprite = sprite;
    destRect = SDL_Rect({0, 0, 0, 0});
    SDL_QueryTexture(this->sprite, NULL, NULL, &destRect.w, &destRect.h);
    scale(scaleSize, scaleSize);
}

Sprite::Sprite(SDL_Texture* sprite, int scaleSizeX, int scaleSizeY) {
    this->sprite = sprite;
    destRect = SDL_Rect({0, 0, 0, 0});
    SDL_QueryTexture(this->sprite, NULL, NULL, &destRect.w, &destRect.h);
    scale(scaleSizeX, scaleSizeY);
}

void Sprite::scale(int scaleX, int scaleY) {
    destRect.w = int(float(scaleX) * destRect.w);
    destRect.h = int(float(scaleY) * destRect.h);
}

void Sprite::render(SDL_Renderer* renderer, int x, int y) {
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopy(renderer, sprite, NULL, &destRect);
}
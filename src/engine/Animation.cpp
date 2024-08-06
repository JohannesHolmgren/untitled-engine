#include "Animation.h"

Animation::Animation() {}

Animation::Animation(std::vector<Sprite> sprites, int frameLength, bool isRepeating) {
    this->sprites = sprites;
    this->isRepeating = isRepeating;
    this->frameLength = frameLength;
    frameCounter = 0;
}

Sprite Animation::getAnimationSprite() {
    // Will trigger if not repeating and have exhausted animation
    int animationLength = frameLength * sprites.size();
    if (frameCounter >= animationLength) {
        return NULL;
    }
    int spriteIndex = frameCounter / frameLength;
    // Update counter
    frameCounter += 1;
    if (isRepeating) {
        frameCounter %= animationLength;
    }
    return sprites[spriteIndex];
}

void Animation::restart() {
    frameCounter = 0;
}
#include "Animator.h"
#include <format> // formatting strings

/**
 * Default constructor
 */
Animator::Animator() {

}

void Animator::addAnimation(std::string name, Animation animation) {
    animations[name] = animation;
}

void Animator::setAnimation(std::string name) {
    // Check if animation exists
    if (!animations.count(name)) {
        printf("Animation %s is not included in animator\n", name.c_str());
        throw std::out_of_range("Key doesn't exist in animator");
    }
    currentAnimation = animations[name];
    currentAnimationName = name;
    currentAnimation.restart();
}

std::string Animator::getCurrentAnimation() {
    return currentAnimationName;
}

Sprite Animator::getSprite() {
    return currentAnimation.getAnimationSprite();
}
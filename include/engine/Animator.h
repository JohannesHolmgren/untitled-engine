/*
    Class Animator

    The animator class holds many animations
    and helps a class easily switch between them
*/

#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <unordered_map>
#include "Animation.h"
#include "Sprite.h"

class Animator {
    private:
        std::unordered_map<std::string, Animation> animations;
        Animation currentAnimation;
        std::string currentAnimationName;

    public:
        Animator();
        void addAnimation(std::string name, Animation animation);
        void setAnimation(std::string name);
        std::string getCurrentAnimation();
        Sprite getSprite();
};

#endif
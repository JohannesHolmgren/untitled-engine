/*
    Class Animation:
    
    The animator is a class which handles animation for
    RenderObjects. It should take a series of sprites
    and switch between them. 

    Should have number of frames between switches
    Should be set to repeat or non-repeat, 
    returning false or similar if end-of-animation
*/

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "Sprite.h"

class Animation {
    private:
        std::vector<Sprite> sprites;
        bool isRepeating;
        int frameLength;
        int frameCounter;

    public:
        Animation();
        Animation(std::vector<Sprite> sprites, int frameLength=1, bool isRepeating=false);
        Sprite getAnimationSprite();
        void restart();

};

#endif
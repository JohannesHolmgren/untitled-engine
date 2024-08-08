/*
    This is a test class, not part of the base implementation
*/

#ifndef DECORATION_H
#define DECORATION_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "RenderObject.h"
#include "State.h"
#include "Key.h"
#include "Animation.h"

class Decoration: public RenderObject {
    public:
        Decoration(std::vector<Sprite> sprites, int x, int y);
        void update(State* state) override;
        std::string name = "Decoration";
    private:
        std::pair<float, float> pos;
        Animation animation;
};

#endif
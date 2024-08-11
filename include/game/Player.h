/*
    This is a test class, not part of the base implementation
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "RenderObject.h"
#include "State.h"
#include "Key.h"
#include "Animation.h"
#include "Animator.h"

class Player: public RenderObject {
    public:
        Player(std::vector<Sprite> sprites, int x, int y);
        void update(State* state) override;
        std::string name = "Player";
    private:
        const float speed = 100;
        std::pair<float, float> pos;
        Animation animation;
        Animator animator;
        void handleKeyInput(State* state);
        void moveToPos();
};

#endif
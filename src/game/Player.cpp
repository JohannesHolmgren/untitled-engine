#include "Player.h"
#include <iostream>
#include "Key.h"

Player::Player(std::vector<Sprite> sprites, int x, int y)
    : RenderObject(sprites[0], x, y) {
    // Initialize the Render Object
    animation = Animation(sprites, 10, true);
    pos.first = float(x);
    pos.second = float(y);
}

void Player::update(State* state) {
    handleKeyInput(state);
    setSprite(animation.getAnimationSprite());
}

void Player::handleKeyInput(State* state) {
    // Handle input
    if (state->getPressedKeys()[Key::K_W]) {
        pos.second -= speed * state->getDeltaTime();
    }
    if (state->getPressedKeys()[Key::K_S]) {
        pos.second += speed * state->getDeltaTime();
    }
    if (state->getPressedKeys()[Key::K_A]) {
        pos.first -= speed * state->getDeltaTime();
    }
    if (state->getPressedKeys()[Key::K_D]) {
        pos.first += speed * state->getDeltaTime();
    }
    moveToPos();
}

// Move renderobject parent to where player is
void Player::moveToPos() {
    int x = int(pos.first);
    int y = int(pos.second);
    RenderObject::setPos(x, y);
}
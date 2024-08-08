#include "Decoration.h"
#include <iostream>
#include "Key.h"

Decoration::Decoration(std::vector<Sprite> sprites, int x, int y)
    : RenderObject(sprites[0], x, y) {
    // Initialize the Render Object
    animation = Animation(sprites, 10, true);
    pos.first = float(x);
    pos.second = float(y);
}

void Decoration::update(State* state) {
    setSprite(animation.getAnimationSprite());
}
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "RenderObject.h"
#include "Engine.h"
#include "Sprite.h"
#include "Player.h"

int main(int argc, char* argv[]) {
    Engine engine;

    engine.init();


    Sprite sprite0 = engine.loadSprite("assets/fish/swimming_0.png", 2);
    Sprite sprite1 = engine.loadSprite("assets/fish/swimming_1.png", 2);
    Sprite sprite2 = engine.loadSprite("assets/fish/swimming_2.png", 2);
    Sprite sprite3 = engine.loadSprite("assets/fish/swimming_3.png", 2);
    std::vector<Sprite> sprites{sprite0, sprite1, sprite2, sprite3};
    engine.addObject(std::make_unique<Player>(sprites, 200, 200));

    engine.start();
    engine.quit();

    return 1;
}

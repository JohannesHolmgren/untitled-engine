#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "RenderObject.h"
#include "Engine.h"
#include "Sprite.h"
#include "Player.h"
#include "Decoration.h"

int main(int argc, char* argv[]) {
    Engine engine;

    engine.init();

    std::vector<Sprite> sprites = engine.loadSpritesFromFolder("assets/player/walk/", 4);
    auto player = std::make_shared<Player>(sprites, 1000, 1000);
    auto decoration = std::make_shared<Decoration>(sprites, 1200, 1000);
    engine.addObject(player);
    engine.addObject(decoration);
    engine.camera.setFocusObject(player);
    engine.camera.setOffset(0, 100);

    engine.start();
    engine.quit();

    return 1;
}

#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "State.h"
#include "RenderObject.h"
#include "Key.h"
#include "Clock.h"
#include "Camera.h"

class Engine {
    private:
        // SDL_Window* window = nullptr;
        // SDL_Renderer* renderer = nullptr;
        const int DEFAULT_SCREEN_WIDTH = 1200;
        const int DEFAULT_SCREEN_HEIGHT = 800;
        bool running = false;
        std::vector<std::shared_ptr<RenderObject>> renderObjects;
        State state = State();
        Clock gameClock;

    public:
        Camera camera;
        Engine();
        bool init();
        void quit();
        void start();
        void stop();
        void addObject(std::shared_ptr<RenderObject> obj);
        Sprite loadSprite(std::string path, int scaleSize);
        std::vector<Sprite> loadSpritesFromFolder(std::string path, int scaleSize);

    private:
        void handleEvents();
        void updateAll();
        void run();
        void updateDeltaTime();

};

#endif
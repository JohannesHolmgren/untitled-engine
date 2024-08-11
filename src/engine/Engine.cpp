#include "Engine.h"
#include <iostream>
#include <filesystem>
#include "RenderObject.h"
#include "Key.h"


Engine::Engine() {
    gameClock = Clock();
}

/** 
 * Initialize the program by initializing SDL2 for video,
 * SDL2_image for PNG loading and create program window and renderer.
 * 
 * @return 'true' if program was successfully initialized, 'false' otherwise.
 */
bool Engine::init() {
    // Inititalize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Could not initialize. SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize camera
    camera.init(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

    printf("Program initiated successfully\n");
    return true;
}

/** 
 * Quit the program by destroying window and renderer
 * and quitting the subsystems.
 */
void Engine::quit() {

    // Destroy renderer

    // Destroy camera (window)
    camera.quit();

    // Quit SDL Subsystems
    SDL_Quit();

    printf("Program quit successfully\n");
}

/** 
 * Start the program loop.
 */
void Engine::start() {
    // Start program loop

    running = true;
    run();
}

void Engine::stop() {
    // Stop the main loop
    running = false;
}

void Engine::addObject(std::shared_ptr<RenderObject> obj) {
    renderObjects.push_back(obj);
}

Sprite Engine::loadSprite(std::string path, int scaleSize) {
    // Load image at specified path to surface
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    if (tmpSurface == NULL) {
        printf("Unable to load image %s. SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        throw std::runtime_error("Unable to load image " + path + "SDL_image Error: " + IMG_GetError());
    }
    // Convert surface to texture
    SDL_Texture* newSpriteTexture = camera.textureFromSurface(tmpSurface);
    if (newSpriteTexture == NULL) {
        printf("Could not create texture. SDL_image Error: %s\n", IMG_GetError());
        throw std::runtime_error("Unable to load image " + path + "SDL_image Error: " + IMG_GetError());
    }
    // Get rid of old loaded surface
    SDL_FreeSurface(tmpSurface);
    return Sprite(newSpriteTexture, scaleSize);
}

std::vector<Sprite> Engine::loadSpritesFromFolder(std::string path, int scaleSize) {
    std::vector<Sprite> sprites;
    try {
        if(std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
            for (const auto& file : std::filesystem::directory_iterator(path)) {
                Sprite sprite = loadSprite(file.path(), scaleSize);
                sprites.push_back(sprite);
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        printf("Could not load sprites from directory %s\n. Filesystem error: %s", path.c_str(), e.what());
    }
    return sprites;
}

/* ======== Private methods ======== */

void Engine::handleEvents() {
    // Reset keys pressed and released
    // state.resetAllKeys();
    // Handle all events on the event queue
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT:
            stop();
            break;
        case SDL_KEYDOWN:
            state.setKeyPressed(intToKey(e.key.keysym.sym));    
            break;
        case SDL_KEYUP:
            state.setKeyReleased(intToKey(e.key.keysym.sym));
        default:
            break;
        }
    }
}

/**
 * Update all render objects
 */
void Engine::updateAll() {
    for (auto& obj: renderObjects) {
        obj->update(&state);
    }
}

/**
 * Set the time passed since last frame
 * to the state of the program.
 */
void Engine::updateDeltaTime() {
    
}

/** 
 * Main loop of the running program
 */
void Engine::run() {
    while (running) {
        updateDeltaTime();
        handleEvents();
        updateAll();
        camera.update(renderObjects); // Renders everything
        gameClock.update(60); // Pass FPS to restrict to
        state.setDeltaTime(gameClock.getDeltaTime()); // Transfer delta time to state
    }
}
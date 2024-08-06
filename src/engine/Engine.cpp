#include "Engine.h"
#include <iostream>
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
    // Create window
    window = SDL_CreateWindow(
        "Untitled Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        printf("Window could not be created. SDL Error: %s\n", SDL_GetError());
        return false;
    }
    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created. SDL Error: %s\n", SDL_GetError());
        return false;
    }
    // Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not be initialized. SDL_image error: %s\n", IMG_GetError());
        return false;
    }

    printf("Program initiated successfully\n");
    return true;
}

/** 
 * Quit the program by destroying window and renderer
 * and quitting the subsystems.
 */
void Engine::quit() {

    // Destroy renderer

    // Destroy window
    SDL_DestroyWindow(window);
    window = NULL;

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

void Engine::addObject(std::unique_ptr<RenderObject> obj) {
    renderObjects.push_back(std::move(obj));
}

Sprite Engine::loadSprite(std::string path, int scaleSize) {
    // Load image at specified path to surface
    SDL_Surface* tmpSurface = IMG_Load(path.c_str());
    if (tmpSurface == NULL) {
        printf("Unable to load image %s. SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return NULL;
    }
    // Convert surface to texture
    SDL_Texture* newSpriteTexture;
    newSpriteTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    if (newSpriteTexture == NULL) {
        printf("Could not create texture from %s. SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return NULL;
    }
    // Get rid of old loaded surface
    SDL_FreeSurface(tmpSurface);
    return Sprite(newSpriteTexture, scaleSize);
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
 * Render all objects to render and refresh window.
 */
void Engine::renderAll() {
    // Clear screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Render all objects TBD
    for (auto& obj: renderObjects) {
        obj->render(renderer);
    }

    // Update screen
    SDL_RenderPresent(renderer);
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
        renderAll();
        updateAll();
        gameClock.update(60); // Pass FPS to restrict to
        state.setDeltaTime(gameClock.getDeltaTime()); // Transfer delta time to state
    }
}
#include "Camera.h"
#include "SDL2/SDL_image.h"
#include <vector>

Camera::Camera() {
}

bool Camera::init(int width, int height) {
    // Create window
    window = SDL_CreateWindow(
        "Untitled Engine",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        printf("Window could not be created. SDL Error: %s\n", SDL_GetError());
        return false;
    }
    // Set camera rect to rect of window (can be changed later)
    SDL_GetWindowSize(window, &cameraRect.w, &cameraRect.h);

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
    // Create world texture (NOTE! Temporary size for now)
    world = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 2*width, 2*height);
    if (!world) {
        printf("Failed to create world texture. SDL Error: %s\n", SDL_GetError());
        return false;
    }
    printf("Camera initialized successfully\n");
    return true;
}

/**
 * Set the object for the camera to follow around
 */
void Camera::setFocusObject(RenderObject* obj) {
    objectInFocus = std::unique_ptr<RenderObject>(obj);
}

/**
 * Set the x- any y-offset from the object in focus.
 */
void Camera::setOffset(int dx, int dy) {
    offset.first = dx;
    offset.second = dy;
}

/**
 * Get the camera offset from the object in focus
 */
std::pair<int, int> Camera::getOffset() {
    return offset;
}

std::pair<int, int> Camera::getPosition() {
    return std::pair<int, int>{cameraRect.x, cameraRect.y};
}

/**
 * Get the width and height of the camera's view
 */
std::pair<int, int> Camera::getSize() {
    return std::pair<int, int>{cameraRect.w, cameraRect.h};
}
/**
 * Render the world onto the window
 */
void Camera::render(std::vector<std::unique_ptr<RenderObject>>& renderObjects) {
    // Clear Screen
    // SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderClear(renderer);

    // Render objects onto world after clearing
    SDL_SetRenderTarget(renderer, world);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    for (auto& obj: renderObjects) {
        obj->render(renderer);
    }

    // Render world onto window after clearing
    SDL_SetRenderTarget(renderer, nullptr);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, world, &cameraRect, nullptr);

    // Update screen
    SDL_RenderPresent(renderer);
}

SDL_Window* Camera::getWindow() {
    return window;
}

void Camera::quit() {
    // Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;
}

SDL_Texture* Camera::textureFromSurface(SDL_Surface* surface) {
    SDL_Texture* newSpriteTexture;
    newSpriteTexture = SDL_CreateTextureFromSurface(renderer, surface);
    return newSpriteTexture;
}
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
void Camera::setFocusObject(std::shared_ptr<RenderObject> obj) {
    if (obj) {
        objectInFocus = std::move(obj);
        printf("Position of object: %d, %d\n", objectInFocus->getPos().first, objectInFocus->getPos().second);
    }
    else {
        printf("Couldn't set object in focus\n");
    }
}

/**
 * Remove focus for camera, making it stay in position
 */
void Camera::unsetFocusObject() {
    objectInFocus = nullptr;
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

void Camera::updatePositionFromFocusObject() {
    if (!objectInFocus) return;

    std::pair<int, int> playerPos = objectInFocus->getPos();
    std::pair<int, int> playerSize = objectInFocus->getSize();
    int playerMiddleX = playerPos.first + playerSize.first / 2;
    int playerMiddleY = playerPos.second + playerSize.second / 2;

    cameraRect.x = playerMiddleX - cameraRect.w / 2;
    cameraRect.y = playerMiddleY - cameraRect.h / 2;
}

/**
 * Render the world onto the window
 */
void Camera::render(std::vector<std::shared_ptr<RenderObject>>& renderObjects) {

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

void Camera::update(std::vector<std::shared_ptr<RenderObject>>& renderObjects) {
    // Move camera to center on focus Object
    updatePositionFromFocusObject();
    printf("Pos: %d, %d\n", cameraRect.x, cameraRect.y);
    render(renderObjects);
}
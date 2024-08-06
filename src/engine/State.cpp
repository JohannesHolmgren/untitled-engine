#include <unordered_map>
#include "State.h"

State::State() {
    deltaTime = 0;
}

// Get the map of keys that are currently pressed
std::unordered_map<Key, bool> State::getPressedKeys() {
    return keyPressed;
}

// Set a key as pressed
void State::setKeyPressed(Key key) {
    keyPressed[key] = true;
}

// Set a key as released
void State::setKeyReleased(Key key) {
    keyPressed[key] = false;
}

// Reset all key states
void State::resetAllKeys() {
    keyPressed.clear();
}

// Set delta time. Called every frame from main loop
void State::setDeltaTime(float newDeltaTime) {
    deltaTime = newDeltaTime;
}

// Get delta time
float State::getDeltaTime() {
    return deltaTime;
}
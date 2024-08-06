#include "Clock.h"
#include <thread>
#include <iostream>

Clock::Clock() {
    lastTimeStamp = std::chrono::high_resolution_clock::now();
    deltaTime = 0.0f;
    isFirstUpdate = true;
}

// Get the time since the last time the clock was updated
float Clock::getElapsedTime() {
    auto currentTimeStamp = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = currentTimeStamp - lastTimeStamp;
    return elapsed.count();

}

void Clock::updateDeltaTime() {
    auto currentTimeStamp = std::chrono::high_resolution_clock::now();
    // Don't set delta time for the first update to remove big initial spike
    if (isFirstUpdate) {
        isFirstUpdate = false;
    } else {
        std::chrono::duration<float> elapsed = currentTimeStamp - lastTimeStamp;
        deltaTime = elapsed.count();
    }
    lastTimeStamp = currentTimeStamp;
}

// Stop the program to restrict the frame rate
void Clock::constrainFPS(int fps, float elapsed) {
    float frameLength = 1 / float(fps);
    float sleepDurationMili = (frameLength - elapsed) * 1000; // In miliseconds
    if (sleepDurationMili > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(sleepDurationMili)));
    }
}

void Clock::update(int fps) {
    // First get elapsed time since last frame
    auto elapsed = getElapsedTime();
    // Constrain to fram rate if necessary
    constrainFPS(fps, elapsed);
    // Set delta time (the time this frame took)
    updateDeltaTime();
}

float Clock::getDeltaTime() const {
    return deltaTime;
}
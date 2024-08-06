#ifndef CLOCK_H
#define CLOCK_H

#include "time.h"
#include <chrono>

class Clock {
    private:
        std::chrono::high_resolution_clock::time_point lastTimeStamp;
        float deltaTime;
        bool isFirstUpdate;

    public:
        Clock();
        float getElapsedTime();
        void updateDeltaTime();
        void constrainFPS(int fps, float elapsed);
        void update(int fps);
        float getDeltaTime() const;

};

#endif
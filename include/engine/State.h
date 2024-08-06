#ifndef STATE_H
#define STATE_H

#include "Key.h"
#include <unordered_map>

class State {
    private:
        // To save key events
        std::unordered_map<Key, bool> keyPressed;
        // Time
        float deltaTime;

    public:
        State();
        // Methods for key events
        std::unordered_map<Key, bool> getPressedKeys();
        void setKeyPressed(Key key);
        void setKeyReleased(Key key);
        void resetAllKeys();
        // Methods for time
        void setDeltaTime(float newDeltaTime);
        float getDeltaTime();
};

#endif
#ifndef KEYBOARDCONTROLLERCOMPONENT_HPP
#define KEYBOARDCONTROLLERCOMPONENT_HPP

#include <glm/glm.hpp>
#include <string>

struct KeyboardControllerComponent {
    float velocity;

    KeyboardControllerComponent(float velocity = 0.0) : velocity(velocity) {
    }
};

#endif

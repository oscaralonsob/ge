#ifndef TARGETMOVEMENTCOMPONENT_HPP
#define TARGETMOVEMENTCOMPONENT_HPP

#include <glm/glm.hpp>
#include <string>

struct TargetMovementComponent {
    float velocity;
    std::string tag;

    TargetMovementComponent(float velocity = 0.0, std::string tag = "")
        : velocity(velocity), tag(tag) {
    }
};

#endif

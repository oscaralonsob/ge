#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include <glm/glm.hpp>

struct BoxColliderComponent {
    glm::vec2 size;
    glm::vec2 offset;

    BoxColliderComponent(glm::vec2 size = glm::vec2(0.0, 0.0),
                         glm::vec2 offset = glm::vec2(0.0, 0.0)) {
        this->size = size;
        this->offset = offset;
    }
};

#endif

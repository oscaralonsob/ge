#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <glm/glm.hpp>

struct SpriteComponent {
    glm::vec2 size;

    SpriteComponent(glm::vec2 size = glm::vec2(0.0, 0.0)) {
        this->size = size;
    }
};

#endif

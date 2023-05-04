#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <glm/glm.hpp>
#include <string>

struct SpriteComponent {
    std::string textureId;
    glm::vec2 size;
    glm::vec2 offset;

    SpriteComponent(std::string textureId = "", glm::vec2 size = glm::vec2(0.0, 0.0), glm::vec2 offset = glm::vec2(0.0, 0.0)) {
        this->textureId = textureId;
        this->size = size;
        this->offset = offset;
    }
};

#endif

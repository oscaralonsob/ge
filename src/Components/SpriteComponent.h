#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <glm/glm.hpp>
#include <string>

struct SpriteComponent {
    std::string textureId;
    int zIndex;
    glm::vec2 size;
    glm::vec2 offset;
    bool isFixed;

    SpriteComponent(std::string textureId = "", int zIndex = 0, glm::vec2 size = glm::vec2(0.0, 0.0), glm::vec2 offset = glm::vec2(0.0, 0.0), bool isFixed = false) {
        this->textureId = textureId;
        this->zIndex = zIndex;
        this->size = size;
        this->offset = offset;
        this->isFixed = isFixed;
    }

    bool operator < (const SpriteComponent other) const {
        return zIndex < other.zIndex;
    }
};

#endif

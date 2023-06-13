#ifndef GUIELEMENTCOMPONENT_HPP
#define GUIELEMENTCOMPONENT_HPP

#include <glm/glm.hpp>

struct GUIElementComponent {
    glm::vec2 position;
    glm::vec2 size;
    bool isFixed;

    GUIElementComponent(glm::vec2 position = glm::vec2(0.0, 0.0),
                        glm::vec2 size = glm::vec2(1.0, 1.0),
                        bool isFixed = true)
        : position(position), size(size), isFixed(isFixed) {
    }
};

#endif
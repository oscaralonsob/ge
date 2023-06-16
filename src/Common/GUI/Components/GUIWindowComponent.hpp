#ifndef GUIWINDOWCOMPONENT_HPP
#define GUIWINDOWCOMPONENT_HPP

#include "GUIElementComponent.hpp"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

struct GUIWindowComponent : public GUIElementComponent {
    SDL_Color color;

    GUIWindowComponent(glm::vec2 position = glm::vec2(0.0, 0.0),
                       glm::vec2 size = glm::vec2(1.0, 1.0),
                       SDL_Color color = {15, 15, 15, 215})
        : GUIElementComponent(position, size), color(color) {
    }
};

#endif
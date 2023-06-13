#ifndef GUILABELCOMPONENT_HPP
#define GUILABELCOMPONENT_HPP

#include "GUIElementComponent.hpp"

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

struct GUITextLabelComponent : public GUIElementComponent {
    std::string text;
    std::string assetId;
    SDL_Color color;

    GUITextLabelComponent(glm::vec2 position = glm::vec2(0.0, 0.0),
                          glm::vec2 size = glm::vec2(1.0, 1.0),
                          std::string text = "", std::string assetId = "",
                          SDL_Color color = {255, 255, 255})
        : GUIElementComponent(position, size), text(text), assetId(assetId),
          color(color) {
    }
};

#endif
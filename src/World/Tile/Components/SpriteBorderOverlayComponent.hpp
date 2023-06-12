#ifndef SPRITEBORDEROVERLAYCOMPONENT_HPP
#define SPRITEBORDEROVERLAYCOMPONENT_HPP

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

struct SpriteBorderOverlayComponent {
    SDL_Color color;

    SpriteBorderOverlayComponent(SDL_Color color = {255, 255, 255}) {
        this->color = color;
    }
};

#endif

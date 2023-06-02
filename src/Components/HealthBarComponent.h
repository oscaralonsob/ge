#ifndef HEALTHBARCOMPONENT_H
#define HEALTHBARCOMPONENT_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <string>

struct HealthBarComponent {
    std::string assetId;

    HealthBarComponent(std::string assetId = "") {
        this->assetId = assetId;
    }
};

#endif

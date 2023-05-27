#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include <SDL2/SDL.h>
#include <glm/glm.hpp>

struct ProjectileEmitterComponent {
    glm::vec2 projectileVelocity;
    int projectileFrequency;
    int projectileDuration;
    int hitDamage;
    bool isFriendly;//TODO: migrate to tags aand gruops maybe
    int lastEmissionTime;

    ProjectileEmitterComponent(glm::vec2 projectileVelocity = glm::vec2(0.0, 0.0), int projectileFrequency = 0, int projectileDuration = 10000, int hitDamage = 10, bool isFriendly = false) {
        this->projectileVelocity = projectileVelocity;
        this->projectileFrequency = projectileFrequency;
        this->projectileDuration = projectileDuration;
        this->hitDamage = hitDamage;
        this->isFriendly = isFriendly;
        this->lastEmissionTime = SDL_GetTicks();
    }
};

#endif

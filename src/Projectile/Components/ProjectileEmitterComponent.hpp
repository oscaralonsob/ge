#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include "../../Physics2D/Vec2.hpp"

#include <SDL2/SDL.h>

using namespace ge::physics2d;

struct ProjectileEmitterComponent {
    Vec2 projectileVelocity;
    int projectileFrequency;
    int projectileDuration;
    int hitDamage;
    bool isFriendly; // TODO: migrate to tags aand gruops maybe
    int lastEmissionTime;
    // TODO: correct init
    ProjectileEmitterComponent(Vec2 projectileVelocity = Vec2(0.0, 0.0),
                               int projectileFrequency = 0,
                               int projectileDuration = 10000,
                               int hitDamage = 10, bool isFriendly = false) {
        this->projectileVelocity = projectileVelocity;
        this->projectileFrequency = projectileFrequency;
        this->projectileDuration = projectileDuration;
        this->hitDamage = hitDamage;
        this->isFriendly = isFriendly;
        this->lastEmissionTime = SDL_GetTicks();
    }
};

#endif

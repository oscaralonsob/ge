#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

#include <SDL2/SDL.h>

struct ProjectileComponent {
    int projectileDuration;
    int hitDamage;
    int startTime;

    ProjectileComponent(int duration = 0, int hitDamage = 0) {
        this->projectileDuration = duration;
        this->hitDamage = hitDamage;
        this->startTime = SDL_GetTicks();
    }
};

#endif

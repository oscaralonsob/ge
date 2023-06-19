#ifndef PROJECTILECOMPONENT_H
#define PROJECTILECOMPONENT_H

#include <SDL2/SDL.h>

struct ProjectileComponent {
    int projectileDuration;
    int hitDamage;
    bool isFriendly; // TODO: migrate to tags aand gruops maybe
    int startTime;

    ProjectileComponent(int duration = 0, int hitDamage = 0,
                        bool isFriendly = false) {
        this->projectileDuration = duration;
        this->hitDamage = hitDamage;
        this->isFriendly = isFriendly;
        this->startTime = SDL_GetTicks();
    }
};

#endif

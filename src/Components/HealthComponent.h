#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include <glm/glm.hpp>

struct HealthComponent {
    int maxHealth;
    int currentHealth;

    HealthComponent(int maxHealth = 0, int currentHealth = 0) {
        this->maxHealth = maxHealth;
        this->currentHealth = currentHealth;
    }
};

#endif

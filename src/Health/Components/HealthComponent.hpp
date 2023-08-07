#ifndef HEALTHCOMPONENT_HPP
#define HEALTHCOMPONENT_HPP

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

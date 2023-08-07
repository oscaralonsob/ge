#ifndef DAMAGECOMPONENT_HPP
#define DAMAGECOMPONENT_HPP

#include <glm/glm.hpp>

struct DamageComponent {
    int damage;

    DamageComponent(int damage = 0) {
        this->damage = damage;
    }
};

#endif

#ifndef HITPOINTCOMPONENT_HPP
#define HITPOINTCOMPONENT_HPP

#include <glm/glm.hpp>

struct HitPointComponent {
    int maxHitPoint;
    int currentHitPoint;

    HitPointComponent(int maxHitPoint = 0, int currentHitPoint = 0) {
        this->maxHitPoint = maxHitPoint;
        this->currentHitPoint = currentHitPoint;
    }
};

#endif

#ifndef COLLIDERCOMPONENT_HPP
#define COLLIDERCOMPONENT_HPP

#include "../../../Physics2D/Vec2.hpp"

using namespace ge::physics2d;

struct BoxColliderComponent {
    Vec2 size;
    Vec2 offset;

    BoxColliderComponent(Vec2 size = Vec2(0.0, 0.0),
                         Vec2 offset = Vec2(0.0, 0.0)) {
        this->size = size;
        this->offset = offset;
    }
};

#endif

#ifndef RIGIDBODYCOMPONENT_HPP
#define RIGIDBODYCOMPONENT_HPP

#include "../../../Physics2D/Vec2.hpp"

using namespace ge::physics2d;

struct RigidBodyComponent {
    Vec2 velocity;

    RigidBodyComponent(Vec2 velocity = Vec2(0.0, 0.0)) {
        this->velocity = velocity;
    }
};

#endif

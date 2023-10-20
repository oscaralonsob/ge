#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP

#include "../../../Physics2D/Vec2.hpp"

using namespace ge::physics2d;

struct TransformComponent {
    Vec2 position;
    Vec2 scale;
    double rotation;

    TransformComponent(Vec2 position = Vec2(0.0, 0.0),
                       Vec2 scale = Vec2(1.0, 1.0), double rotation = 0.0) {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

#endif

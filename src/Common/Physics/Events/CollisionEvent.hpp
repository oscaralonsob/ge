#ifndef COLLISIONEVENT_HPP
#define COLLISIONEVENT_HPP

#include "../../ECS/Entity.hpp"

class CollisionEvent : public Event {
public:
    Entity a;
    Entity b;

    CollisionEvent(Entity a, Entity b) : a(a), b(b){};
};

#endif
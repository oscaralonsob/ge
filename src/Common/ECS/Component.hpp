#ifndef COMPONENT_H
#define COMPONENT_H

#include "BaseComponent.hpp"

template <typename T>
class Component : public BaseComponent {
public:
    static int GetId() {
        static int id = nextId++;
        return id;
    }
};

#endif
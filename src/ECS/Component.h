#ifndef COMPONENT_H
#define COMPONENT_H

#include "BaseComponent.h"

template <typename T>
class Component: public BaseComponent {
    private:

    public:
        static int GetId();
};

#endif
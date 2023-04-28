#include "Component.h"

int BaseComponent::nextId = 0;

template <typename T>
int Component<T>::GetId() {
    static int id = nextId++;
    return id;
}
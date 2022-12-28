#include "Component.h"

template <typename T>
int Component<T>::GetId() {
    static int id = nextId++;
    return id;
}
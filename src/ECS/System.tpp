#include "System.h"

template <typename T> 
void System::RequireComponent() {
    const int componentId = Component<T>::GetId();
    componentSignature.set(componentId);
}

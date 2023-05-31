#ifndef IPOOL_H
#define IPOOL_H

// TODO: can be modified and avoid interface
class IPool {
public:
    virtual ~IPool() = default;
    virtual void RemoveEntityFromPool(int entityId) = 0;
};

#endif
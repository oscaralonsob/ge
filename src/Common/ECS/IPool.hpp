#ifndef IPOOL_HPP
#define IPOOL_HPP

// TODO: can be modified and avoid interface
class IPool {
public:
    virtual ~IPool() = default;
    virtual void RemoveEntityFromPool(int entityId) = 0;
};

#endif
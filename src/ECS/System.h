#ifndef SYSTEM_H
#define SYSTEM_H

#include "../Logger/Logger.h"
#include "Component.h"
#include "Entity.h"

#include <algorithm>
#include <bitset>
#include <memory>
#include <vector>

const unsigned int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

class System {
private:
    Signature componentSignature;
    std::vector<Entity> entities;

protected:
    class Registry* registry;
    std::shared_ptr<Logger> logger;

public:
    System(Registry* registry, std::shared_ptr<Logger> logger);
    ~System() = default;

    void AddEntityToSystem(Entity entity);
    void RemoveEntityFromSystem(Entity entity);
    std::vector<Entity> GetSystemEntities() const;
    const Signature& GetComponentSignature() const;

    template <typename T>
    void RequireComponent();
};

#include "System.tpp"

#endif
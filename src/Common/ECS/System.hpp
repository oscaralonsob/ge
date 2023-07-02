#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "../Events/EventBus.hpp"
#include "Component.hpp"
#include "Entity.hpp"

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
    std::shared_ptr<class Registry> registry;
    std::shared_ptr<EventBus> eventBus;
    std::shared_ptr<class AssetStore> assetStore;

public:
    System(std::shared_ptr<Registry> registry,
           std::shared_ptr<EventBus> eventBus,
           std::shared_ptr<AssetStore> assetStore);
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
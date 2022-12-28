#ifndef SYSTEM_H
#define SYSTEM_H

#include <bitset>
#include <vector>
#include <algorithm>
#include "Entity.h"

const unsigned int MAX_COMPONENTS = 32;

typedef std::bitset<MAX_COMPONENTS> Signature;

class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntityes() const;
        const Signature& GetComponentSignature() const;

        template <typename T> void RequireComponent();
};

#endif
#ifndef POOL_HPP
#define POOL_HPP

#include "IPool.hpp"

#include <unordered_map>
#include <vector>

// TODO: look for tpp files
template <typename T>
class Pool : public IPool {
private:
    std::vector<T> data;
    int currentSize;

    std::unordered_map<int, int> entityIdToIndex;
    std::unordered_map<int, int> indexToEntityId;

public:
    Pool(int size = 100) {
        this->currentSize = 0;
        data.resize(size);
    }

    virtual ~Pool() = default;

    bool IsEmpty() const {
        return currentSize == 0;
    }

    int GetSize() const {
        return currentSize;
    }

    void Resize(int size) {
        data.resize(size);
    }

    void Clear() {
        data.clear();
        currentSize = 0;
    }

    // TODO: method not used I think
    void Add(T object) {
        data.push_back(object);
    }

    void Set(int entityId, T object) {
        if (entityIdToIndex.find(entityId) != entityIdToIndex.end()) {
            int index = entityIdToIndex[entityId];
            data[index] = object;
        } else {
            int index = currentSize;
            entityIdToIndex.emplace(entityId, index);
            indexToEntityId.emplace(index, entityId);
            if (currentSize >= (int)data.size()) { // TODO: verify this
                data.resize(currentSize * 2);
            }
            data[index] = object;
            currentSize++;
        }
    }

    void Remove(int entityId) {
        int indexOfRemoved = entityIdToIndex[entityId];
        int swapIndex = currentSize - 1;
        data[indexOfRemoved] = data[swapIndex];

        int swapEntityId = indexToEntityId[swapIndex];
        entityIdToIndex[swapEntityId] = indexOfRemoved;
        indexToEntityId[indexOfRemoved] = swapEntityId;

        entityIdToIndex.erase(entityId);
        indexToEntityId.erase(swapIndex);

        currentSize--;
    }

    void RemoveEntityFromPool(int entityId) override {
        if (entityIdToIndex.find(entityId) != entityIdToIndex.end()) {
            Remove(entityId);
        }
    }

    T& Get(int entityId) {
        int index = entityIdToIndex[entityId];
        return static_cast<T&>(data[index]);
    }
};

#endif
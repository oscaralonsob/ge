#ifndef POOL_H
#define POOL_H

#include <vector>

#include "IPool.h"

template <typename T>
class Pool: public IPool {
    private:
        std::vector<T> data;

    public:
        Pool(int size = 100) {
            data.resize(size);
        }

        virtual ~Pool() = default;

        bool IsEmpty() const {
            return data.empty();
        }

        int GetSize() const {
            return data.size();
        }

        void Resize(int size) {
            data.resize();
        }

        void Clear() {
            data.clear();
        }

        void Add(T object) {
            data.push_back(object);
        }

        void Set(int index, T object) {
            data[index] = object;
        }

        T& Get(int index)  {
            return static_cast<T&>(data[index]);
        }

        T& operator [](unsigned int index) {
            return static_cast<T&>(data[index]);
        }
};

#endif
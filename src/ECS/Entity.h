#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity {
    private:
        int id;

    public:
        Entity(int id);
        int GetId() const;

        bool operator ==(const Entity& other) const;
        bool operator !=(const Entity& other) const;
        bool operator <(const Entity& other) const;
        bool operator >(const Entity& other) const;
};

#endif
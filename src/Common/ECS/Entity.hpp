#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

class Entity {
private:
    int id;

public:
    Entity(int id);
    int GetId() const;

    bool operator==(const Entity& other) const;
    bool operator!=(const Entity& other) const;
    bool operator<(const Entity& other) const;
    bool operator>(const Entity& other) const;
};

#endif
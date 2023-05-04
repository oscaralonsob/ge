#ifndef ENTITY_H
#define ENTITY_H

class Entity {
    private:
        int id;
        class Registry* registry;

    public:
        Entity(int id, Registry* registry);
        int GetId() const;

        bool operator ==(const Entity& other) const;
        bool operator !=(const Entity& other) const;
        bool operator <(const Entity& other) const;
        bool operator >(const Entity& other) const;

        //TODO: not a fan of this but it works.
        Registry* GetRegistry() const;
};

#endif
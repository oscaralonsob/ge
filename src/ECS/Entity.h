#ifndef ENTITY_H
#define ENTITY_H

class Entity {
    private:
        int id;

    public:
        Entity(int id): id(id) {};
        int GetId() const;
};

#endif
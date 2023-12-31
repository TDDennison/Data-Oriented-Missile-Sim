#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <string>

#include "../Entity.h"

class EntityManager
{
    public:

    static Entity CreateEntity();

    private:
    inline static unsigned int nextId = 1;
};

#endif //ENTITY_MANAGER_H
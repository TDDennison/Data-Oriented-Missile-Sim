#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <array>
#include <iostream>
#include <map>
#include <stdexcept>

#include "../Entity.h"

typedef unsigned int EntityId;

struct ComponentInstance {
    unsigned int index;
};

template<typename ComponentType, unsigned int MaxComponents>
class ComponentManager
{
    private:

    template <unsigned int MaxData>
    struct ComponentData {
        unsigned int size = 0;
        ComponentType data[MaxData];
    };

    public:

    // Add a new component to the entity
    unsigned int Add(Entity ent, ComponentType ct)
    {
        unsigned int newInstance;
        newInstance = componentData.size;
        componentData.data[newInstance] = ct;
        entityMap[ent.id] = newInstance;
        ++componentData.size;
        return newInstance;
    }

    // Lookup the component related to an entity
    ComponentType& Lookup(Entity ent)
    {
        if (entityMap.find(ent.id) == entityMap.end()) { 
            printf("Entity with id: %d did not have an associated component.\n", ent.id);
            throw std::runtime_error("Entity did not exist!");
        }

        unsigned int instance = entityMap[ent.id];
        return componentData.data[instance];
    }

    // Destroy the component related to an entity
    void Destroy(Entity ent)
    {
        if (componentData.size > 1) // If there are more than one component being managed, manage them, else just decrement the index.
        {
            std::cout << "Attempting to remove entity from component manager: " << ent.id << std::endl;

            unsigned int instance = entityMap[ent.id];
            unsigned int lastComponent = {componentData.size - 1};

            // Find the ID of the last entity
            // Get the memory address of the data
            ComponentType* lastAddr = &(componentData.data[lastComponent]);

            EntityId movedEntity;
            if(GetEntityByComponentInstance(lastAddr, movedEntity))
            {
                std::cout << "Found the last entity by component instance. Last entity id is: " << movedEntity << std::endl;
                componentData.data[instance] = componentData.data[lastComponent];

                std::cout << "Erasing entity from entity map: " << ent.id << std::endl;
                entityMap.erase(ent.id);

                // Update the map for the moved entity as well
                std::cout << "Adjusting instance of: " << movedEntity << " to: " << instance << std::endl;
                entityMap[movedEntity] = instance;
            }
            else
            {
                return;
            }
        }

        --componentData.size;
    }

    bool GetEntityByComponentInstance(ComponentType* component, EntityId& entity)
    {
        for(std::map<unsigned int, unsigned int>::iterator iter = entityMap.begin(); iter != entityMap.end(); ++iter)
        {
            unsigned int key =  iter->first;

            unsigned int instance = entityMap[key];            
            if (&(componentData.data[instance]) == component)
            {
                entity = key;
                return true;
            }
        }

        std::cout << "Could not find entity by component instance." << std::endl;
        return false;
    }

    protected:
    
    ComponentData<MaxComponents> componentData;
    std::map<unsigned int, unsigned int> entityMap;
};

#endif //COMPONENT_MANAGER_H
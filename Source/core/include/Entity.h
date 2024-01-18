#ifndef ENTITY_H
#define ENTITY_H

/* WARNING: All Entity objects should be created through the EntityManager for 
*  safe handling.
*/
struct Entity
{
    unsigned int id;

    bool operator== (Entity const& other) {
        return id == other.id;
    }
};


#endif //ENTITY_H
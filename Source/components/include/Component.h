#ifndef COMPONENT_H
#define COMPONENT_H

#include <bitset>

// Number of bits that comprise a component ID.
static inline const int COMPONENT_ID_FIELD_SIZE = 16;
static inline const uint16_t DEFAULT_COMPONENT_ID = 0x0000;

class Component
{
    public:
    // Constructors
    Component();
    Component(uint16_t id);

    unsigned short getId();
    uint8_t        getComponentId();
    uint8_t        getEntityId();
    std::bitset<COMPONENT_ID_FIELD_SIZE> getIdBitset();
    void setId(uint16_t id);

    private:
    std::bitset<COMPONENT_ID_FIELD_SIZE> id_ = 0x0000;
};

#endif //COMPONENT_H
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
    Component() : id_(DEFAULT_COMPONENT_ID) {}
    Component(uint16_t id) : id_(id) {}

    inline unsigned short getId() { return static_cast<unsigned short>(id_.to_ulong()); }
    inline uint8_t        getComponentId() { uint8_t temp = 0; return temp | id_.to_ulong(); }
    inline uint8_t        getEntityId() { uint8_t temp = 0; return temp | id_.to_ulong() >> 8; }
    inline std::bitset<COMPONENT_ID_FIELD_SIZE> getIdBitset() { return id_; }
    void setId(uint16_t id) { id_ = id; }

    private:
    std::bitset<COMPONENT_ID_FIELD_SIZE> id_ = 0x0000;
};

#endif //COMPONENT_H
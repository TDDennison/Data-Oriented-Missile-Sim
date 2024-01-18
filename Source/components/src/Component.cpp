#include "Component.h"

Component::Component() : id_(DEFAULT_COMPONENT_ID) {}


Component::Component(uint16_t id) : id_(id) {}


unsigned short Component::getId() { return static_cast<unsigned short>(id_.to_ulong()); }


uint8_t Component::getComponentId() { uint8_t temp = 0; return temp | id_.to_ulong(); }


uint8_t Component::getEntityId() { uint8_t temp = 0; return temp | id_.to_ulong() >> 8; }


std::bitset<COMPONENT_ID_FIELD_SIZE> Component::getIdBitset() { return id_; }


void Component::setId(uint16_t id) { id_ = id; }

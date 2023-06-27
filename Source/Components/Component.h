#ifndef COMPONENT_H
#define COMPONENT_H

#include <bitset>

struct Component
{
    std::bitset<16> componentId = 0x0000;
};

#endif //COMPONENT_H
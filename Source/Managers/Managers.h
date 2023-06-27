#ifndef MANAGERS_H
#define MANAGERS_H

#include "../Components/SoftwareComponent.h"

static const int MaxComponents = 10;

typedef ComponentManager<SoftwareComponent, MaxComponents> TestSoftwareManager;

#endif //MANAGERS_H
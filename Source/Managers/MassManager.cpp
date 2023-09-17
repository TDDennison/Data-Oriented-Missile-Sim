#include <memory>

#include "../Components/Utilities.h"
#include "MassManager.h"

MassManager* MassManager::GetInstance() {
    if(instance == nullptr) { 
        instance = new MassManager(); 
    }

    return instance;
}

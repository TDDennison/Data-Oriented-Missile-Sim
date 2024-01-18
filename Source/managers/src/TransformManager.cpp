#include <memory>

#include "Utilities.h"
#include "TransformManager.h"

TransformManager* TransformManager::GetInstance() {
    if(instance == nullptr) {
        instance = new TransformManager(); 
    }
    return instance;
}

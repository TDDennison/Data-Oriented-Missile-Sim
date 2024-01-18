#include "AttributesManager.h"

AttributesManager::AttributesManager(){};

AttributesManager* AttributesManager::GetInstance() {
    if(instance == nullptr) { instance = new AttributesManager(); }
    return instance;
}

// Set the data associated with the attribute.
void AttributesManager::SetAttribute(const char *attributeName, const char *value)
{
    // Find the attribute in the attribute map.
    if (dataMap.find(attributeName) == dataMap.end() ||
        typeMap.find(attributeName) == typeMap.end())
    {
        // Throw an exception because the attribute has not been registered.
        std::string error = "Attribute has not been registered: ";
        error.append(attributeName);
        throw std::invalid_argument(error);
    }

    std::stringstream ss(value);
    switch(typeMap[attributeName])
    {
        case Core::Enumerations::AttributeType::BOOLEAN:
        {
            bool temp;
            ss >> temp;
            SetData<bool>(attributeName, temp);
            break;
        }
        case Core::Enumerations::AttributeType::UINT8:
        {
            uint8_t temp;
            ss >> temp;
            SetData<uint8_t>(attributeName, temp);
            break;
        }
        case Core::Enumerations::AttributeType::UINT16:
        {
            uint16_t temp;
            ss >> temp;
            SetData<uint16_t>(attributeName, temp);
            break;
        }
        case Core::Enumerations::AttributeType::UINT32:
        {
            uint32_t temp;
            ss >> temp;
            SetData<uint32_t>(attributeName, temp);
            break;
        }
        case Core::Enumerations::AttributeType::UINT64:
        {
            uint64_t temp;
            ss >> temp;
            SetData<uint64_t>(attributeName, temp);
            break;
        }
        case Core::Enumerations::AttributeType::INT8:
        {
            int8_t temp;
            ss >> temp;
            SetData<int8_t>(attributeName, temp);
            break;

        }
        case Core::Enumerations::AttributeType::INT16:
        {
            int16_t temp;
            ss >> temp;
            SetData<int16_t>(attributeName, temp);
            break;
        }
        case Core::Enumerations::AttributeType::INT32:
        {
            int32_t temp;
            ss >> temp;
            SetData<int32_t>(attributeName, temp);
            break;
        }
        case Core::Enumerations::AttributeType::INT64:
        {
            int64_t temp;
            ss >> temp;
            SetData<int64_t>(attributeName, temp);
            break;
        }
        case Core::Enumerations::AttributeType::FLOAT:
        {
            float temp;
            ss >> temp;
            SetData<float>(attributeName, temp);
            break;
        }
        case Core::Enumerations::AttributeType::DOUBLE:
        {
            double temp;
            ss >> temp;
            SetData<double>(attributeName, temp);
            break;
        }
        default:
        {
            std::cout << "Unhandled attribute type!" << std::endl;
        }
    }
}

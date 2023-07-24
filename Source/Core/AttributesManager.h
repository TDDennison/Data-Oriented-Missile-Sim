#ifndef ATTRIBUTES_MANAGER_H
#define ATTRIBUTES_MANAGER_H

#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "../Utilities.h"

// Singleton used to store a default list of missile attributes and their values.
// This stored data should come from input file parsing directly. When constructing
// components from the stored data for monte carlo capability, the data should be 
// perturbed AFTER reading from this storage. These stored values should not be 
// manipulated at any time after input parsing has completed.
class AttributesManager
{
    public:
    static AttributesManager* GetInstance() {
        if(instance == nullptr) { instance = new AttributesManager(); }
        return instance;
    }

    // Get the data associated with the attribute.
    template<typename T>
    T GetAttribute(const char *attributeName)
    {
        // Find the attribute in the attribute map.
        if (dataMap.find(attributeName) == dataMap.end())
        {
            // Throw an exception because the attribute has not been defined.
            std::cout << "Could not find attribute by name: " << attributeName << std::endl;
        }

        // Cast the attribute to the desired type.
        unsigned char bytes[sizeof(T)];
        int index = dataMap[attributeName];
        for (int i = 0; i < sizeof(T); ++i){
            bytes[i] = dataVector[index + i];
        }

        // Copy the data out in bytes.
        T data;
        std::memcpy(&data, bytes, sizeof(T));

        // Return the attribute data.
        return data;
    }

    // Set the data associated with the attribute.
    void SetAttribute(const char *attributeName, const char *value)
    {
        // Find the attribute in the attribute map.
        if (dataMap.find(attributeName) == dataMap.end() ||
            typeMap.find(attributeName) == typeMap.end())
        {
            // Throw an exception because the attribute has not been defined.
            std::cout << "Attribute has not been registered: " << attributeName << std::endl;
            return;
        }

        std::stringstream ss(value);
        switch(typeMap[attributeName])
        {
            case AttributeType::BOOLEAN:
            {
                bool temp;
                ss >> temp;
                SetData<bool>(attributeName, temp);
                break;
            }
            case AttributeType::UINT8:
            {
                uint8_t temp;
                ss >> temp;
                SetData<uint8_t>(attributeName, temp);
                break;
            }
            case AttributeType::UINT16:
            {
                uint16_t temp;
                ss >> temp;
                SetData<uint16_t>(attributeName, temp);
                break;
            }
            case AttributeType::UINT32:
            {
                uint32_t temp;
                ss >> temp;
                SetData<uint32_t>(attributeName, temp);
                break;
            }
            case AttributeType::UINT64:
            {
                uint64_t temp;
                ss >> temp;
                SetData<uint64_t>(attributeName, temp);
                break;
            }
            case AttributeType::INT8:
            {
                int8_t temp;
                ss >> temp;
                SetData<int8_t>(attributeName, temp);
                break;

            }
            case AttributeType::INT16:
            {
                int16_t temp;
                ss >> temp;
                SetData<int16_t>(attributeName, temp);
                break;
            }
            case AttributeType::INT32:
            {
                int32_t temp;
                ss >> temp;
                SetData<int32_t>(attributeName, temp);
                break;
            }
            case AttributeType::INT64:
            {
                int64_t temp;
                ss >> temp;
                SetData<int64_t>(attributeName, temp);
                break;
            }
            case AttributeType::FLOAT:
            {
                float temp;
                ss >> temp;
                SetData<float>(attributeName, temp);
                break;
            }
            case AttributeType::DOUBLE:
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

    template<typename T>
    void SetData(const char *attributeName, T value)
    {
        int index = dataMap[attributeName];
        const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&value);

        for (int i = 0; i < sizeof(T); ++i){
            dataVector[index + i] = *(ptr + i);
        }
    }

    // Add a new attribute to the map with the given data.
    template<typename T>
    void AddAttribute(const char *attributeName, AttributeType type, T value)
    {
        // If the attribute is already in the map, throw an exception.
        if (dataMap.find(attributeName) != dataMap.end())
        {
            // Throw an exception because the attribute has not been defined.
        }

        // Set the attribute name and the index into the data map.
        int lastIndex = dataVector.size();
        dataMap[attributeName] = lastIndex;
        typeMap[attributeName] = type;

        // Cast the value to bytes and set them into the vector.
        const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&value);
        for (size_t i = 0; i < sizeof(T); ++i){
            dataVector.push_back(*(ptr + i));
        }    
    }

    private:
    AttributesManager(){};
    inline static AttributesManager* instance = nullptr;

    std::map<std::string, int> dataMap{};
    std::map<std::string, AttributeType> typeMap{};
    std::vector<unsigned char> dataVector{};
};

#endif // ATTRIBUTES_H
#ifndef ATTRIBUTES_MANAGER_H
#define ATTRIBUTES_MANAGER_H

#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include "CoreEnumerations.h"

// Singleton used to store a default list of missile attributes and their values.
// This stored data should come from input file parsing directly. When constructing
// components from the stored data for monte carlo capability, the data should be 
// perturbed AFTER reading from this storage. These stored values should not be 
// manipulated at any time after input parsing has completed.
class AttributesManager
{
    public:
    static AttributesManager* GetInstance();

    // Get the data associated with the attribute.
    template<typename T>
    T GetAttribute(const char *attributeName)
    {
        // Find the attribute in the attribute map.
        if (dataMap.find(attributeName) == dataMap.end())
        {
            // Throw an exception because the attribute has not been defined.
            std::string error = "Could not find attribute by name: ";
            error.append(attributeName);
            throw std::invalid_argument(error);
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
    void SetAttribute(const char *attributeName, const char *value);

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
    void AddAttribute(const char *attributeName, Core::Enumerations::AttributeType type, T value)
    {
        // If the attribute is already in the map, throw an exception.
        if (dataMap.find(attributeName) != dataMap.end())
        {
            // Throw an exception because the attribute has already been registered.
            std::string error = "Attribute has already been registered: ";
            error.append(attributeName);
            throw std::invalid_argument(error);
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
    AttributesManager();
    inline static AttributesManager* instance = nullptr;

    std::map<std::string, int> dataMap{};
    std::map<std::string, Core::Enumerations::AttributeType> typeMap{};
    std::vector<unsigned char> dataVector{};
};

#endif // ATTRIBUTES_H
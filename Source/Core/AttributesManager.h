#ifndef ATTRIBUTES_MANAGER_H
#define ATTRIBUTES_MANAGER_H

#include <cstring>
#include <iostream>
#include <map>
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
    T GetAttribute(const char * attributeName)
    {
        // Find the attribute in the attribute map.
        if (dataMap.find(attributeName) == dataMap.end())
        {
            // Throw an exception because the attribute has not been defined.
        }

        // Cast the attribute to the desired type.
        unsigned char bytes[sizeof(T)];

        int index = dataMap[attributeName];
        for (size_t i = 0; i < sizeof(T); ++i){
            bytes[i] = dataVector.at(index + i);
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
        }

        switch(typeMap[attributeName])
        {
            case AttributeType::BOOLEAN:
            {
                SetData<bool>(attributeName, value);
                break;
            }
        }
    }

    template<typename T>
    void SetData(const char *attributeName, const char *value)
    {
        int index = dataMap[attributeName];
        const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&value);

        for (size_t i = 0; i < sizeof(T); ++i){
            dataVector.at(index + i) = *(ptr + i);
        }
    }

    // Add a new attribute to the map with the given data.
    template<typename T>
    void AddAttribute(const char * attributeName, AttributeType type, T value)
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
        const char* ptr = reinterpret_cast<const char*>(&value);
        SetAttribute(attributeName, ptr);
    }

    private:
    AttributesManager(){};
    inline static AttributesManager* instance = nullptr;

    // <ATTRIBUTE NAME, ATTRIBUTE TYPE, ATTRIBUTE VALUE ADDRESS, ATTRIBUTE DESCRIPTION>
    std::map<const char *, int> dataMap;
    std::map<const char *, AttributeType> typeMap;
    std::vector<unsigned char> dataVector{};
};

#endif // ATTRIBUTES_H
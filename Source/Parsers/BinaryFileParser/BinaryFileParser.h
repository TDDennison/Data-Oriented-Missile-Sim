#ifndef BINARY_FILE_PARSER_H
#define BINARY_FILE_PARSER_H

#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

#include "../../Components/TransformComponent.h"
#include "../../Components/SolidRocketMotorComponent.h"

class BinaryFileParser
{
    public:
    BinaryFileParser(std::string fileName) : fileName_(fileName) {}

    void Parse()
    {
        std::ifstream inFile(fileName_, std::ios::in | std::ios::binary);
        if(!inFile.good()) { return; }

        float time{0.0f};
        size_t sizeOfComponent{0};
        unsigned int numComponents{0};

        while(!inFile.eof())
        {
            inFile.read((char *)&time, sizeof(time));
            inFile.read(reinterpret_cast<char *>(&sizeOfComponent), sizeof(sizeOfComponent));
            inFile.read(reinterpret_cast<char *>(&numComponents), sizeof(numComponents));

            for (unsigned int i = 0; i < numComponents; ++i)
            {
                SolidRocketMotorComponent srmComponent;
                inFile.read(reinterpret_cast<char *>(&srmComponent), sizeof(SolidRocketMotorComponent));

                // Write the component data 
            }
        }
    }


    private:
    std::string fileName_;
};

#endif // BINARY_FILE_PARSER_H
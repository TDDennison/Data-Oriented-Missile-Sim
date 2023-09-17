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
        if (std::filesystem::exists(fileName_)) { std::cout << "IT EXISTS" << std::endl;}
        std::ifstream inFile(fileName_, std::ios::in | std::ios::binary);
        if(!inFile.good()) { return; }

        while(!inFile.eof())
        {
            float time{};
            size_t sizeOfComponent{0};
            unsigned int numComponents{0};

            inFile.read((char *)&time, sizeof(time));
            inFile.read(reinterpret_cast<char *>(&sizeOfComponent), sizeof(sizeOfComponent));
            inFile.read(reinterpret_cast<char *>(&numComponents), sizeof(numComponents));

            std::cout << "Time: " << time << std::endl;
            std::cout << "Size of Component real: " << sizeof(SolidRocketMotorComponent) << std::endl;
            std::cout << "Size of Component: " << sizeOfComponent << std::endl;
            std::cout << "Number of Components: " << numComponents << std::endl;

            for (unsigned int i = 0; i < numComponents; ++i)
            {
                SolidRocketMotorComponent srmComponent;
                inFile.read(reinterpret_cast<char *>(&srmComponent), sizeof(SolidRocketMotorComponent));
                std::cout << "Propellant mass: " << srmComponent.propellantMass << std::endl;
            }
        }
    }


    private:
    std::string fileName_;
};

#endif // BINARY_FILE_PARSER_H
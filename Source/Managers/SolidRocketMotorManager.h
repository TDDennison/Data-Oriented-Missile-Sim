#ifndef SOLID_ROCKET_MOTOR_MANAGER_H
#define SOLID_ROCKET_MOTOR_MANAGER_H

#include "ComponentManager.h"
#include "../Components/SolidRocketMotorComponent.h"
#include "../Components/Utilities.h"
#include "Managers.h"
#include "../Utilities.h"

class SolidRocketMotorManager : public ComponentManager<SolidRocketMotorComponent, MaxComponents>
{
    public:

    SolidRocketMotorManager(std::string logFileName, BoosterType type) : ComponentManager(logFileName)
    {
        switch(type)
        {
            case FIRST_STAGE:
                name_ = "FS";
                break;
            case SECOND_STAGE:
                name_ = "SS";
                break;
        }
    }

    // Start: ILoggable Implementation
    // ================================================================================
    bool ParseBinaryToText(std::string fileName) override {
        std::ifstream inFile(Configurations::GetInstance()->GetOutputFilePath() / (fileName + Constants::LOG_FILE_EXTENSION_BINARY), std::ios::in | std::ios::binary);
        if(!inFile.good()) { 
            return false; 
        }

        // Open the output file for writing and clear its contents if it already exists.
        std::ofstream outFile(Configurations::GetInstance()->GetOutputFilePath() / (fileName + Constants::LOG_FILE_EXTENSION_TXT), std::ios::out);
        outFile.clear();
        if(!outFile.good()) { 
            return false; 
        }

        float time{0.0f};
        size_t sizeOfComponent{0};
        unsigned int numComponents{0};

        std::stringstream strStream;


        // Write the file header.
        static const std::string COLUMN_HEADER_TIME = "Time";
        static const std::string COLUMN_HEADER_SIZE_OF_COMPONENT = "Size Of Component";
        static const std::string COLUMN_HEADER_NUMBER_OF_COMPONENTS = "Number Of Components";
        static const std::string COLUMN_HEADER_COMPONENT_ID = "Component ID";
        static const std::string COLUMN_HEADER_INERT_MASS = "Inert Mass";
        static const std::string COLUMN_HEADER_PROPELLANT_MASS = "Propellant Mass";
        static const std::string COLUMN_HEADER_THRUST = "Thrust";

        strStream << std::setw(COLUMN_HEADER_TIME.length() + 2) << COLUMN_HEADER_TIME ;
        strStream << std::setw(COLUMN_HEADER_SIZE_OF_COMPONENT.length() + 2) << COLUMN_HEADER_SIZE_OF_COMPONENT ;
        strStream << std::setw(COLUMN_HEADER_NUMBER_OF_COMPONENTS.length() + 2) << COLUMN_HEADER_NUMBER_OF_COMPONENTS ;
        strStream << std::setw(COLUMN_HEADER_COMPONENT_ID.length() + 2) << COLUMN_HEADER_COMPONENT_ID;
        strStream << std::setw(COLUMN_HEADER_INERT_MASS.length() + 2) << COLUMN_HEADER_INERT_MASS ;
        strStream << std::setw(COLUMN_HEADER_PROPELLANT_MASS.length() + 2) << COLUMN_HEADER_PROPELLANT_MASS ;
        strStream << std::setw(COLUMN_HEADER_THRUST.length() + 2) << COLUMN_HEADER_THRUST ;
        strStream << "\n\n";

        outFile << strStream.str();
        strStream.str("");

        while(!inFile.eof())
        {
            inFile.read((char *)&time, sizeof(time));
            inFile.read(reinterpret_cast<char *>(&sizeOfComponent), sizeof(sizeOfComponent));
            inFile.read(reinterpret_cast<char *>(&numComponents), sizeof(numComponents));

            strStream << std::setw(COLUMN_HEADER_TIME.length() + 2) << std::setprecision(4) << time;
            strStream << std::setw(COLUMN_HEADER_SIZE_OF_COMPONENT.length() + 2) << sizeOfComponent;
            strStream << std::setw(COLUMN_HEADER_NUMBER_OF_COMPONENTS.length() + 2) << numComponents;
            
            strStream << "\n";
            outFile << strStream.str();
            strStream.str(""); // Reset the string

            for (unsigned int i = 0; i < numComponents; ++i)
            {
                SolidRocketMotorComponent srmComponent;
                inFile.read(reinterpret_cast<char *>(&srmComponent), sizeof(SolidRocketMotorComponent));

                int whitespaceLength = (COLUMN_HEADER_TIME.length() + 2) + 
                                       (COLUMN_HEADER_SIZE_OF_COMPONENT.length() + 2) +
                                       (COLUMN_HEADER_NUMBER_OF_COMPONENTS.length() + 2);

                strStream << std::setw(whitespaceLength + COLUMN_HEADER_COMPONENT_ID.length() + 2) << srmComponent.getId();
                strStream << std::setw(COLUMN_HEADER_INERT_MASS.length() + 2) << srmComponent.inertMass;
                strStream << std::setw(COLUMN_HEADER_PROPELLANT_MASS.length() + 2) << srmComponent.propellantMass;
                strStream << std::setw(COLUMN_HEADER_THRUST.length() + 2) << srmComponent.thrust;  

                strStream << "\n";
                outFile << strStream.str();
                strStream.str(""); // Reset the string
            }
        }

        outFile.close();
        return true;
    }

    // ================================================================================
    // End: ILoggable Implementation


    private:
    std::string name_;
};

#endif //SOLID_ROCKET_MOTOR_MANAGER_H
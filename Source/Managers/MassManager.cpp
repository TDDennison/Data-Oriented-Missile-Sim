#include <memory>
#include <unistd.h>

#include "../Components/Utilities.h"
#include "MassManager.h"

MassManager* MassManager::GetInstance() {
    if(instance == nullptr) { 
        instance = new MassManager(); 
    }

    return instance;
}

// Start: ILoggable Implementation
// ================================================================================

bool MassManager::ParseBinaryToText(std::string fileName) {
    std::ifstream inFile(Configurations::GetInstance()->GetOutputFilePath() / (fileName + Constants::LOG_FILE_EXTENSION_BINARY), std::ios::in | std::ios::binary);
    if(!inFile.good()) { 
        std::cout << "Encountered an error when opening input file: " << fileName << std::endl;
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

    static const std::string COLUMN_HEADER_MASS = "Mass";
    static const std::string COLUMN_HEADER_POSITION_CG_BODY = "Position CG Body";
    static const std::string COLUMN_HEADER_INERTIA_TENSOR = "Inertia Tensor";
    static const std::string COLUMN_HEADER_NUM_SUBMASSES = "Num Sub Masses";

    strStream << std::setw(COLUMN_HEADER_TIME.length() + 2) << COLUMN_HEADER_TIME ;
    strStream << std::setw(COLUMN_HEADER_SIZE_OF_COMPONENT.length() + 2) << COLUMN_HEADER_SIZE_OF_COMPONENT ;
    strStream << std::setw(COLUMN_HEADER_NUMBER_OF_COMPONENTS.length() + 2) << COLUMN_HEADER_NUMBER_OF_COMPONENTS ;
    strStream << std::setw(COLUMN_HEADER_COMPONENT_ID.length() + 2) << COLUMN_HEADER_COMPONENT_ID;
    
    strStream << std::setw(COLUMN_HEADER_NUM_SUBMASSES.length() + 2) << COLUMN_HEADER_NUM_SUBMASSES;
    strStream << std::setw(COLUMN_HEADER_MASS.length() + 2) << COLUMN_HEADER_MASS;
    strStream << std::setw(COLUMN_HEADER_POSITION_CG_BODY.length() + 2) << COLUMN_HEADER_POSITION_CG_BODY;
    strStream << std::setw(COLUMN_HEADER_INERTIA_TENSOR.length() + 2) << COLUMN_HEADER_INERTIA_TENSOR;

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
            usleep(100000);
            static int counter = 1;
            MassComponent massComponent;
            inFile.read(reinterpret_cast<char *>(&massComponent), sizeof(MassComponent));

            int whitespaceLength = (COLUMN_HEADER_TIME.length() + 2) + 
                                    (COLUMN_HEADER_SIZE_OF_COMPONENT.length() + 2) +
                                    (COLUMN_HEADER_NUMBER_OF_COMPONENTS.length() + 2);

            strStream << std::setw(whitespaceLength + COLUMN_HEADER_COMPONENT_ID.length() + 2) << massComponent.getId();
            strStream << std::setw(COLUMN_HEADER_NUM_SUBMASSES.length() + 2) << static_cast<int>(massComponent.numSubMasses);
            strStream << std::setw(COLUMN_HEADER_MASS.length() + 2) << massComponent.mass;
            strStream << std::setw(COLUMN_HEADER_POSITION_CG_BODY.length() + 2) << "[" << massComponent.position_cg_body.x
                                                                                << " " << massComponent.position_cg_body.y
                                                                                << " " << massComponent.position_cg_body.z << "]";
            // // Write the first row of inertia tensor data.
            // strStream << std::setw(COLUMN_HEADER_INERTIA_TENSOR.length() + 2) << "[" << massComponent.inertiaTensor.data[0]
            //                                                                   << " " << massComponent.inertiaTensor.data[1]  
            //                                                                   << " " << massComponent.inertiaTensor.data[2] << "]\n";
            
            // whitespaceLength += COLUMN_HEADER_COMPONENT_ID.length() + 2;
            // whitespaceLength += COLUMN_HEADER_NUM_SUBMASSES.length() + 2;
            // whitespaceLength += COLUMN_HEADER_MASS.length() + 2;
            // whitespaceLength += COLUMN_HEADER_POSITION_CG_BODY.length() + 2;

            // // Write the second and third rows of inertia tensor data.
            // strStream << std::setw(whitespaceLength + COLUMN_HEADER_INERTIA_TENSOR.length() + 2) << "[" << massComponent.inertiaTensor.data[3]
            //                                                                   << " " << massComponent.inertiaTensor.data[4]  
            //                                                                   << " " << massComponent.inertiaTensor.data[5] << "]\n";
            // strStream << std::setw(COLUMN_HEADER_INERTIA_TENSOR.length() + 2) << "[" << massComponent.inertiaTensor.data[6]
            //                                                                   << " " << massComponent.inertiaTensor.data[7]  
            //                                                                   << " " << massComponent.inertiaTensor.data[8] << "]\n";


            strStream << "\n";
            outFile << strStream.str();
            strStream.str(""); // Reset the string
        }
    }

    outFile.close();
    return true;
}

// End: ILoggable Implementation
// ================================================================================
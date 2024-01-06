#ifndef LOGGING_SYSTEM_H
#define LOGGING_SYSTEM_H

#include <cstring>
#include <string>
#include <fstream>

#include "../Constants.h"
#include "../Core/Configurations.h"

class LoggingSystem
{
    public:

    LoggingSystem(std::string fileName) : 
    fileName_(fileName), 
    outputFile_(Configurations::GetInstance()->GetOutputFilePath() / (fileName_ + Constants::LOG_FILE_EXTENSION_BINARY), std::ios::out | std::ios::binary), 
    bufferIndex_(0){}

    std::string getFileName() { return fileName_; }

    void WriteAll()
    {
        outputFile_.write(buffer_, bufferIndex_);
        outputFile_.close();
    }
    
    void WriteToBuffer(void *obj, size_t sizeOfComponent, unsigned int numComponents, float *time)
    {
        unsigned long sizeOfComponentData = sizeOfComponent * numComponents;
        unsigned long numBytes = sizeof(sizeOfComponent) + sizeof(numComponents) + sizeOfComponentData + sizeof(*time);
        // Make sure there is enough space left in the buffer to write the bytes.
        if (sizeof(buffer_) - bufferIndex_  < numBytes)
        {
            // Swap out the buffer pointers and write the buffer data to disk.
            //outputFile_.open(fileName_.c_str(), std::ios::out | std::ios::binary);
            outputFile_.write(buffer_, bufferIndex_);

            bufferIndex_ = 0;
        }

        // Write the time.
        std::memcpy(buffer_ + bufferIndex_, time, sizeof(*time));
        bufferIndex_ += sizeof(*time);

        // Write the size of the component. (May only have to do this one time, at the beginning)
        std::memcpy(buffer_ + bufferIndex_, &sizeOfComponent, sizeof(sizeOfComponent));
        bufferIndex_ += sizeof(sizeOfComponent);

        // Write the number of components.
        std::memcpy(buffer_ + bufferIndex_, &numComponents, sizeof(numComponents));
        bufferIndex_ += sizeof(numComponents);

        // Write the object data.
        std::memcpy(buffer_ + bufferIndex_, obj, sizeOfComponentData);
        bufferIndex_ += sizeOfComponentData;
    }

    private:

    std::string fileName_;
    std::fstream outputFile_;
    uint bufferIndex_ = 0;
    char buffer_[1048576]{0}; // One megabyte buffer size.
};

#endif //LOGGING_SYSTEM_H
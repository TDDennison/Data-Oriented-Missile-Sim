#include "BinaryLogger.h"

BinaryLogger::BinaryLogger(std::string fileName) : 
                            fileName_(fileName), 
                            outputFile_(Configurations::GetInstance()->GetOutputFilePath() / (fileName_ + Core::Constants::LOG_FILE_EXTENSION_BINARY), std::ios::out | std::ios::binary), 
                            bufferIndex_(0){}

std::string BinaryLogger::getFileName() { return fileName_; }

void BinaryLogger::WriteAll()
{
    outputFile_.write(buffer_, bufferIndex_);
    outputFile_.close();
}

void BinaryLogger::WriteToBuffer(void *obj, size_t sizeOfComponent, unsigned int numComponents, float *time)
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

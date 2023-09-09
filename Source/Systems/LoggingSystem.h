#ifndef LOGGING_SYSTEM_H
#define LOGGING_SYSTEM_H

#include <cstring>
#include <string>
#include <fstream>

class LoggingSystem
{
    public:

    LoggingSystem(std::string fileName) : 
    fileName_(fileName), 
    outputFile_(fileName_, std::ios::out | std::ios::binary), 
    bufferIndex_(0){}

    void WriteAllLogs(float time)
    {
    }
    
    void WriteToBuffer(void *obj, size_t numBytes)
    {
        // Make sure there is enough space left in the buffer to write the bytes.
        if (sizeof(buffer_) - bufferIndex_ < numBytes)
        {
            // Swap out the buffer pointers and write the buffer data to disk.
            //outputFile_.open(fileName_.c_str(), std::ios::out | std::ios::binary);
            outputFile_.write(buffer_, bufferIndex_);

            bufferIndex_ = 0;
        }

        std::memcpy(buffer_ + bufferIndex_, obj, numBytes);
        bufferIndex_ += numBytes;
    }

    private:

    std::string fileName_;
    std::fstream outputFile_;
    uint bufferIndex_ = 0;
    char buffer_[1048576]{0}; // One megabyte buffer size.
};

#endif //LOGGING_SYSTEM_H
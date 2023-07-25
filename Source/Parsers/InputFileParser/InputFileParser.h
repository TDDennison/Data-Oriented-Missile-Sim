#ifndef INPUT_FILE_PARSER_H
#define INPUT_FILE_PARSER_H

#include <filesystem>
#include <fstream>
#include <iostream>

#include "../../Core/AttributesManager.h"

const std::string WHITESPACE = " ";
const std::string COMMENT_DELIMITER = "//";
const std::string COLON_DELIMITER = ":";

// Parse the designated input file for simulation configuration.
class InputFileParser
{
    public:

    InputFileParser(std::filesystem::path filePath){
        TryParse(filePath);
    };

    private:

    std::string GetLine(std::ifstream& inFile)
    {
        std::string line;
        std::getline(inFile, line);

        RemoveComments(line);
        TrimWhitespaceFromEnds(line);

        return line;
    }

    // Remove comments from the string.
    void RemoveComments(std::string& line)
    {
        size_t commentIndex = line.find(COMMENT_DELIMITER);
        if (commentIndex != std::string::npos) {
            // Remove all characters from the start of the comment to the end of the line.
            line.erase(commentIndex);
        }
    }
    
    // Trim whitespace from the left side of the string.
    void LeftTrim(std::string &s)
    {
        size_t start = s.find_first_not_of(WHITESPACE);
        if (!(start == std::string::npos)) { s = s.substr(start); }
    }
    
    // Trim whitespace from the right side of the string.
    void RightTrim(std::string &s)
    {
        size_t end = s.find_last_not_of(WHITESPACE);
        if (!(end == std::string::npos)) { s = s.substr(0, end + 1); }
    }
    
    // Trim whitespace from both sides of the string.
    void TrimWhitespaceFromEnds(std::string &s) {
        LeftTrim(s);
        RightTrim(s);
    }

    bool TryParse(std::filesystem::path filePath) 
    {
        // Open the file for parsing.
        std::ifstream inFile(filePath.string());
        if (!inFile.is_open()) { return false; }

        AttributesManager *attributesManager = AttributesManager::GetInstance();
        std::string line;
        while(!inFile.eof())
        {
            line = GetLine(inFile);
            
            // Find the colon separator and separate the attribute name from the value.
            size_t colonIndex = line.find_first_of(COLON_DELIMITER);
            if (!(colonIndex == std::string::npos)) 
            {
                std::string attributeName = line.substr(0, colonIndex);
                std::string value = line.substr(colonIndex + 1, line.length() - colonIndex);
                TrimWhitespaceFromEnds(value);

                // If there is no value associated with the name, don't try to set it.
                if (!value.empty()) {
                    attributesManager->SetAttribute(attributeName.c_str(), value.c_str());
                }
            }

        }

        return true;
    };
};

#endif //INPUT_FILE_PARSER_H
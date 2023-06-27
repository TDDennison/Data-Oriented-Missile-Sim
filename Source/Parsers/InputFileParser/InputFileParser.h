#ifndef INPUT_FILE_PARSER_H
#define INPUT_FILE_PARSER_H

#include <filesystem>
#include <fstream>
#include <iostream>

const std::string WHITESPACE = " ";
const std::string COMMENT_DELIMITER = "//";

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

        std::string line;
        while(!inFile.eof())
        {
            line = GetLine(inFile);
            
            // Look for 
        }

        return true;
    };
};

#endif //INPUT_FILE_PARSER_H
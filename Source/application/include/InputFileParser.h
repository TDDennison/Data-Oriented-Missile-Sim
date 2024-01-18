#ifndef INPUT_FILE_PARSER_H
#define INPUT_FILE_PARSER_H

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include "DomSimConstants.h"
#include "AttributesManager.h"
#include "Configurations.h"

#include "Vector3.h"

const std::string WHITESPACE = " ";
const std::string COMMENT_DELIMITER = "//";
const std::string COLON_DELIMITER = ":";
const std::string SEMICOLON_DELIMITER = ";";
const std::string PIPE_DELIMITER = "|";

// Parse the designated input file for simulation configuration.
class InputFileParser
{
    public:

    InputFileParser();

    bool TryParse(std::filesystem::path filePath);

    private:

    std::string GetLine(std::ifstream& inFile);

    // Remove comments from the string.
    void RemoveComments(std::string& line);
    
    // Trim whitespace from the left side of the string.
    void LeftTrim(std::string &s);
    
    // Trim whitespace from the right side of the string.
    void RightTrim(std::string &s);
    
    // Trim whitespace from both sides of the string.
    void TrimWhitespaceFromEnds(std::string &s);

    bool isReservedAttribute(std::string attributeName);

    // Return true if North, false if South.
    // Throws exception if neither.
    bool isNorthOrSouth(std::string latitudeStr);

    // Return true if East, false if West.
    // Throws exception if neither.
    bool isEastOrWest(std::string longitudeStr);

    void ParseReservedAttribute(std::string attributeName, std::ifstream &inFile);

    void ParseMissileStartingLocations(std::ifstream &inFile);

    void ParseTargetPoint(std::ifstream &inFile);

    inline static std::string reservedAttributes_[] = {
        DomSim::Constants::RESERVED_ATTRIBUTE_MISSILE_STARTING_LOCATIONS,
        DomSim::Constants::RESERVED_ATTRIBUTE_TARGET_POINTS
    };
};

#endif //INPUT_FILE_PARSER_H
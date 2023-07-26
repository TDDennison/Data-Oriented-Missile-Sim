#ifndef INPUT_FILE_PARSER_H
#define INPUT_FILE_PARSER_H

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

#include "../../Constants.h"
#include "../../Core/AttributesManager.h"
#include "../../Core/Configurations.h"

const std::string WHITESPACE = " ";
const std::string COMMENT_DELIMITER = "//";
const std::string COLON_DELIMITER = ":";
const std::string PIPE_DELIMITER = "|";

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

        // If all that is left is a single space, remove it.
        if (s == " ") { s = ""; }
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

            // Make sure the line is not empty.
            if (line.empty()) { continue; }
            
            // Find the colon separator and separate the attribute name from the value.
            size_t colonIndex = line.find_first_of(COLON_DELIMITER);
            if (!(colonIndex == std::string::npos)) 
            {
                std::string attributeName = line.substr(0, colonIndex);
                std::string value = line.substr(colonIndex + 1, line.length() - colonIndex);
                TrimWhitespaceFromEnds(value);

                // Check if the attribute name is a reserved attribute.
                if (isReservedAttribute(attributeName))
                {
                    // Parse the next lines accordingly.
                    ParseReservedAttribute(attributeName, inFile);

                    continue;
                }

                // If there is no value associated with the name, don't try to set it.
                if (!value.empty()) {
                    attributesManager->SetAttribute(attributeName.c_str(), value.c_str());
                }
                else
                {
                    std::cout << "Attribute: '" << attributeName << "' -- is not a reserved attribute and had no associated value, skipping this attribute." << std::endl;
                }
            }
            else
            {
                std::string error = "Could not parse line: \n-" + line + "-";
                throw std::invalid_argument(error);
            }

        }

        return true;
    };

    bool isReservedAttribute(std::string attributeName)
    {
        for (size_t i = 0; i < reservedAttributes_->size(); ++i)
        {
            if (reservedAttributes_[i] == attributeName) { return true; }
        }

        return false;
    }

    // Return true if North, false if South.
    // Throws exception if neither.
    bool isNorthOrSouth(std::string latitudeStr)
    {
        if(latitudeStr.find_first_of("N") != std::string::npos ||
           latitudeStr.find_first_of("n") != std::string::npos)
        { return true; }

        if(latitudeStr.find_first_of("S") != std::string::npos ||
           latitudeStr.find_first_of("s") != std::string::npos)
        { return false; }

        std::string error = "Could not parse latitude: " + latitudeStr + ". Make sure it includes 'N' or 'S'.";
        throw std::invalid_argument(error);
    }

    // Return true if East, false if West.
    // Throws exception if neither.
    bool isEastOrWest(std::string longitudeStr)
    {
        if(longitudeStr.find_first_of("E") != std::string::npos ||
           longitudeStr.find_first_of("e") != std::string::npos)
        { return false; }

        if(longitudeStr.find_first_of("W") != std::string::npos ||
           longitudeStr.find_first_of("w") != std::string::npos)
        { return true; }

        std::string error = "Could not parse latitude: " + longitudeStr + ". Make sure it includes 'E' or 'W'.";
        throw std::invalid_argument(error);
    }

    void ParseReservedAttribute(std::string attributeName, std::ifstream &inFile)
    {
        if (attributeName == Constants::RESERVED_ATTRIBUTE_MISSILE_STARTING_LOCATIONS)
        {
            ParseMissileStartingLocations(inFile);
        }
        else
        {
            std::cout << "Could not parse reserved attribute" << std::endl;
        }
    }

    void ParseMissileStartingLocations(std::ifstream &inFile)
    {
        std::cout << "Parsing missile starting locations" << std::endl;

        std::string line;
        while(!inFile.eof())
        {
            line = GetLine(inFile);

            // Split the line on the | delimiter.
            size_t pipeIndex = line.find_first_of(PIPE_DELIMITER);
            if (!(pipeIndex == std::string::npos)) 
            {
                // Ignore the missile number that is the first field in the line.
                std::string latlon = line.substr(pipeIndex + 1, line.length() - pipeIndex);
                TrimWhitespaceFromEnds(latlon);

                // Split the line again to separate the latitude and longitude values.
                size_t pipeIndex = latlon.find_first_of(PIPE_DELIMITER);
                if (!(pipeIndex == std::string::npos)) 
                {
                    std::string lat = latlon.substr(0, pipeIndex);
                    std::string lon = latlon.substr(pipeIndex + 1, latlon.length() - pipeIndex);

                    TrimWhitespaceFromEnds(lat);
                    TrimWhitespaceFromEnds(lon);

                    // Create a lat/lon pair and store it for later.
                    std::stringstream lat_ss(lat);
                    std::stringstream lon_ss(lon);

                    float temp_lat = std::stof(lat_ss.str());
                    float temp_lon = std::stof(lon_ss.str());

                    // Check to make sure the sign is correct.
                    if (!isNorthOrSouth(lat_ss.str())) { temp_lat *= -1.0; }
                    if (!isEastOrWest(lon_ss.str()))   { temp_lon *= -1.0; }

                    std::pair<float, float> latLonPair = std::make_pair(temp_lat, temp_lon);
                    Configurations::GetInstance()->AddMissileStartingLocation(latLonPair);
                }
            }

            // If the line is empty, that signifies that the missile starting locations section is over.
            if (line.empty()) { return; }
        }
    }

    inline static std::string reservedAttributes_[] = {Constants::RESERVED_ATTRIBUTE_MISSILE_STARTING_LOCATIONS };
};

#endif //INPUT_FILE_PARSER_H
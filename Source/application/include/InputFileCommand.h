#ifndef INPUT_FILE_COMMAND_H
#define INPUT_FILE_COMMAND_H

#include <filesystem>
#include <iostream>
#include <utility>
#include <string>

#include "Configurations.h"
#include "CommandLineCommand.h"

class InputFileCommand : public CommandLineCommand
{
    public:
    InputFileCommand() 
    {
        shortDesignator = "-i";
        longDesignator = "--input_file";
    }

    ~InputFileCommand(){};

    std::pair<bool, std::string> TryParse(CommandLineArguments& args) override
    {
        // Remove the designator.
        std::string designator = args.GetNext();

        // Make sure there is an argument.
        if(!args.HasNext())
        {
            return std::pair<bool, std::string>(false, designator + " not given follow on argument.");
        }

        // Get the next argument.
        std::string filepath_str = args.GetNext();
        std::filesystem::path filepath(filepath_str);
        if (!std::filesystem::exists(filepath))
        {
            return std::pair<bool, std::string>(false, "Filepath does not exist: " + filepath_str);
        }

        // Filepath exists, set up the file for parsing.
        Configurations::GetInstance()->SetInputFilePath(filepath);

        return std::pair<bool, std::string>(true, "");
    }
};

#endif //INPUT_FILE_COMMAND_H
#include "CommandLineArguments.h"
#include "CommandLineParser.h"
#include "Commands/InputFileCommand.h"

#include <iostream>

CommandLineParser::CommandLineParser()
{
    InputFileCommand* inputFileCommand = new InputFileCommand();
    RegisterCommand(inputFileCommand);
}

bool CommandLineParser::TryParse(int argc, char** argv)
{
    CommandLineArguments cmdLineArgs;
    cmdLineArgs.index = 0;
    cmdLineArgs.argc = argc;
    cmdLineArgs.argv = argv;

    std::cout << "Starting to parse command line arguments." << std::endl;

    for(; cmdLineArgs.index < cmdLineArgs.argc; ++cmdLineArgs.index)
    {
        std::string arg = cmdLineArgs.argv[cmdLineArgs.index];
        std::pair<bool, std::string> returnPair = commandMap[arg]->TryParse(cmdLineArgs);

        if(!returnPair.first)
        {
            std::cout << returnPair.second << std::endl;
            return false;
        }
    }

    std::cout << "Done parsing command line arguments." << std::endl;

    return true;
}

void CommandLineParser::RegisterCommand(CommandLineCommand* command)
{
    //Add the command to the command map based on its designators
    commandMap[command->getShortDesignator()] = command;
    commandMap[command->getLongDesignator()]  = command;
}
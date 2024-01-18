#ifndef COMMAND_LINE_PARSER_H
#define COMMAND_LINE_PARSER_H

#include <map>
#include <string>
#include <vector>

#include "CommandLineCommand.h"

//Forward declarations
class CommandLineCommand;

class CommandLineParser
{
    public:
    CommandLineParser();
    ~CommandLineParser(){};

    bool TryParse(int argc, char** argv);

    private:
    std::map<std::string, CommandLineCommand*> commandMap;

    void RegisterCommand(CommandLineCommand*);
};

#endif //COMMAND_LINE_PARSER_H
#ifndef COMMAND_LINE_COMMAND_H
#define COMMAND_LINE_COMMAND_H

#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "../CommandLineArguments.h"
#include "../CommandLineParser.h"

class CommandLineCommand
{
    public:
    CommandLineCommand(){};
    virtual ~CommandLineCommand(){};

    virtual std::pair<bool, std::string> TryParse(CommandLineArguments& args) 
    {
        return std::pair<bool, std::string>(false, "CommandLineCommand TryParse not overridden!");
    }

    std::string getShortDesignator() { return shortDesignator; }
    std::string getLongDesignator() { return longDesignator; }

    protected:

    std::string shortDesignator;
    std::string longDesignator;
};

#endif //COMMAND_LINE_COMMAND_H
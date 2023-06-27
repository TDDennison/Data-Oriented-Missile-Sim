#ifndef COMMAND_LINE_ARGUMENTS
#define COMMAND_LINE_ARGUMENTS

#include <string>

class CommandLineArguments
{
    public:

    int index = 0;
    int argc;
    char** argv;

    std::string GetNext()
    {
        std::string retString = argv[index];
        ++index;
        return retString;
    }

    bool HasNext()
    {
        return index < argc;
    }

    std::string PeekNext()
    {
        return argv[index];
    }
};

#endif //COMMAND_LINE_ARGUMENTS

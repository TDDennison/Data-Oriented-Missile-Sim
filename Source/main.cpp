#include <chrono>
#include <iostream>

#include "Core/Configurations.h"

#include "Parsers/CommandLineParser/CommandLineParser.h"
#include "Parsers/InputFileParser/InputFileParser.h"

#include "Simulation.h"

int main(int argc, char** argv)
{
    std::cout << "Data Oriented Missile Simulation running!" << std::endl;

    // Create a vector of strings from the command line arguments.
    std::vector<std::string> cmdArgs(argv+1, argv + argc); // Remove the first argument as it is the arg calling this function.

    // Try to parse the command line arguments.
    CommandLineParser commandLineParser;
    bool parseSucceeded = commandLineParser.TryParse(argc-1, argv+1);
    if(!parseSucceeded) { return 1; }

    #ifdef RUN_UNIT_TESTS

    #include "_UnitTests/_unitTests.h"

    UnitTests::RunAllTests();

    #else // Run the program for analysis

    // Validate the run configurations.
    std::pair<bool, std::string> configurationsValid = Configurations::GetInstance()->ValidateConfigurations();
    if(!configurationsValid.first)
    {
        std::cout << configurationsValid.second << std::endl;
        return 1;
    }

    // Parse the input file.
    InputFileParser inFileParser(Configurations::GetInstance()->GetInputFilePath());

    // Create a timer to measure the total real time needed to run the simulation.
    auto start = std::chrono::high_resolution_clock::now();

    // Run the simulation.
    Simulation *simulation = Simulation::GetInstance();
    simulation->Run();

    auto finish = std::chrono::high_resolution_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(finish-start);

    std::cout << "Time elapsed: " << milliseconds.count() << " milliseconds." << std::endl;

    #endif //RUN_UNIT_TESTS

    return 0;
}


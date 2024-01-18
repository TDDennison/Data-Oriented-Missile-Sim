#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

#include "ComponentUtilities.h"
#include "Vector3.h"

// Singleton class used to hold pertinent configuration data for a run that may be needed
// during the course of the run.
class Configurations
{
    public:
    static Configurations* GetInstance();

    std::filesystem::path GetInputFilePath();
    void SetInputFilePath(std::filesystem::path inputPath);

    std::filesystem::path GetOutputFilePath();
    void SetOutputFilePath(std::filesystem::path outputPath);

    //================================================================================
    // Missile Starting Locations
    //================================================================================
    void AddMissileStartingLocation(std::pair<float, float> latLonPair);

    std::vector<std::pair<float, float>>& GetMissileStartingLocations();

    //================================================================================
    // Target Intercept Points
    //================================================================================
    void AddTargetInterceptPoint(Vector3 interceptPoint);

    std::vector<Vector3>& GetTargetInterceptPoints();

    // Checks to make sure that all configurations that are necessary for a run to start are set properly.
    std::pair<bool, std::string> ValidateConfigurations();

    private:
    Configurations();
    inline static Configurations* instance = nullptr;

    std::filesystem::path inputFilePath_;
    std::filesystem::path outputFilePath_{std::filesystem::path("/home/trevor/Desktop/GitRepos/DOMSim") / "Outputs"}; // Path relative to the current working directory the simulation is being run from. Converted to absolute path when retreived for use.

    std::vector<std::pair<float, float>> missileStartingLocations_{};
    std::vector<Vector3> targetInterceptPoints_{};
};

#endif //CONFIGURATIONS_H
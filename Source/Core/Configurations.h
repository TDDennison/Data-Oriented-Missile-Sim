#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <filesystem>
#include <string>
#include <utility>
#include <vector>

// Singleton class used to hold pertinent configuration data for a run that may be needed
// during the course of the run.
class Configurations
{
    public:
    static Configurations* GetInstance() {
        if(instance == nullptr) { instance = new Configurations(); }
        return instance;
    }

    std::filesystem::path GetInputFilePath() { return inputFilePath_; }
    void SetInputFilePath(std::filesystem::path inputPath) { inputFilePath_ = inputPath; }

    void AddMissileStartingLocation(std::pair<float, float> latLonPair)
    {
        missileStartingLocations_.push_back(latLonPair);
    }

    std::vector<std::pair<float, float>>& GetMissileStartingLocations()
    {
        return missileStartingLocations_;
    }

    // Checks to make sure that all configurations that are necessary for a run to start are set properly.
    std::pair<bool, std::string> ValidateConfigurations()
    {
        if(inputFilePath_.empty()) { return std::pair<bool, std::string>(false, "Input file path has not been declared.");}

        // All configurations valid
        return std::pair<bool, std::string>(true, "");
    }

    private:
    Configurations(){};
    inline static Configurations* instance = nullptr;

    std::filesystem::path inputFilePath_;

    std::vector<std::pair<float, float>> missileStartingLocations_{};
};

#endif //CONFIGURATIONS_H
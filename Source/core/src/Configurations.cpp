#include "Configurations.h"

Configurations::Configurations(){};

Configurations* Configurations::GetInstance() {
    if(instance == nullptr) { instance = new Configurations(); }
    return instance;
}

std::filesystem::path Configurations::GetInputFilePath() { return inputFilePath_; }
void Configurations::SetInputFilePath(std::filesystem::path inputPath) { inputFilePath_ = inputPath; }

std::filesystem::path Configurations::GetOutputFilePath() { return std::filesystem::absolute(outputFilePath_); }
void Configurations::SetOutputFilePath(std::filesystem::path outputPath) { outputFilePath_ = outputPath; }

void Configurations::AddMissileStartingLocation(std::pair<float, float> latLonPair)
{
    missileStartingLocations_.push_back(latLonPair);
}

std::vector<std::pair<float, float>>& Configurations::GetMissileStartingLocations()
{
    return missileStartingLocations_;
}

void Configurations::AddTargetInterceptPoint(Vector3 interceptPoint)
{
    targetInterceptPoints_.push_back(interceptPoint);
}

std::vector<Vector3>& Configurations::GetTargetInterceptPoints()
{
    return targetInterceptPoints_;
}


// Checks to make sure that all configurations that are necessary for a run to start are set properly.
std::pair<bool, std::string> Configurations::ValidateConfigurations()
{
    if(inputFilePath_.empty()) { return std::pair<bool, std::string>(false, "Input file path has not been declared.");}

    // All configurations valid
    return std::pair<bool, std::string>(true, "");
}
